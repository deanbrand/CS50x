from booq import app
from flask import render_template, redirect, url_for, flash, request, session, jsonify
from booq.models import Item, User
from booq.forms import RegisterForm, LoginForm, PurchaseItemForm
from booq import db
from flask_login import login_user, logout_user, login_required, current_user
from sqlalchemy import desc
import time
import numpy as np
import datetime


@app.route('/')
@app.route('/home')
def home_page():
    return render_template('home.html')


@app.route('/market')
@login_required
def market_page():
    items = Item.query.order_by(desc('ratings_count')).limit(20)
    owned_items = Item.query.filter_by(owner=current_user.id)
    cartsize = len(session['cart'])
    return render_template('market.html', items=items, owned_items=owned_items, cartsize=cartsize)


@app.route('/register', methods=['GET', 'POST'])
def register_page():
    form = RegisterForm()
    if form.validate_on_submit():
        user_to_create = User(username=form.username.data,
                              email_address=form.email_address.data,
                              password=form.password1.data)
        db.session.add(user_to_create)
        db.session.commit()
        login_user(user_to_create)
        flash(
            f"Account created successfully! You are now logged in as {user_to_create.username}", category='success')
        return redirect(url_for('market_page'))
    if form.errors != {}:  # If there are not errors from the validations
        for err_msg in form.errors.values():
            flash(
                f'There was an error with creating a user: {err_msg}', category='danger')

    return render_template('register.html', form=form)


@app.route('/login', methods=['GET', 'POST'])
def login_page():
    form = LoginForm()
    if form.validate_on_submit():
        attempted_user = User.query.filter_by(
            username=form.username.data).first()
        if attempted_user and attempted_user.check_password_correction(
                attempted_password=form.password.data
        ):
            login_user(attempted_user)
            flash(
                f'Success! You are logged in as: {attempted_user.username}', category='success')
            return redirect(url_for('market_page'))
        else:
            flash('Username and password are not match! Please try again',
                  category='danger')

    return render_template('login.html', form=form)


@app.route('/logout')
def logout_page():
    logout_user()
    flash("You have been logged out!", category='info')
    return redirect(url_for("home_page"))


@app.route('/cart_fetch', methods=['POST'])
def cart_fetch():
    if request.method == 'POST':
        result = request.get_json()
        if 'cart' not in session:
            session['cart'] = []

        session['cart'].append(result)
        session.modified = True

        return redirect(url_for('cart_page'))


@app.route('/cart')
def cart_page():
    day = (datetime.datetime.now() + datetime.timedelta(days=2)).date()
    if "0" in day.strftime("%d"):
        day = day.strftime("%A, %d %B %Y").replace(", 0", ", ")
    else:
        day = day.strftime("%A, %d %B %Y")
    bitems = []
    cartids = []
    prices = []
    for i in range(len(session['cart'])):
        cartids.append(session['cart'][i])
    for i in range(len(cartids)):
        bitems.append(Item.query.get(cartids[i]))
        prices.append(bitems[i].price)
    if session['cart'] != []:
        return render_template('cart.html', bitems=bitems, cize=len(bitems), total=np.round(sum(prices), 2), day=day)
    else:
        bitems = []
        cartids = []
        prices = []
        return render_template('cart.html', bitems='', cize=len(bitems), total=0.00, day=day)


@app.route('/cart_clear', methods=['POST'])
def cart_clear():
    session['cart'] = []
    session['cart'].clear()
    return redirect(url_for('cart_page'))


@app.route('/cart_add', methods=['POST'])
def cart_add():
    time.sleep(2)
    bid = request.form['bookid']
    if bid not in session['cart']:
        session['cart'].append(bid)

    session.modified = True
    return redirect(url_for('market_page'))


@app.route('/search', methods=['GET', 'POST'])
def search():
    if request.method == "POST":
        q = request.form['book']
        if q:
            search = "%{}%".format(q)
            data = Item.query.filter(Item.title.like(search)).order_by(
                desc('ratings_count')).all()
        else:
            data = []
        return render_template('search.html', data=data)
    return render_template('search.html')
