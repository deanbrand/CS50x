// Add to Cart Animation
const cartButtons = document.querySelectorAll(".cart-button");
// const removeItem = document.getElementsByClassName(".remove_item");
const clCart = document.querySelectorAll('[name="clear"]');
let basket = JSON.parse(localStorage.getItem("data")) || [];

// console.log(cartButtons);
console.log(basket);

cartButtons.forEach((button) => {
  button.addEventListener("click", cartClick);
});

// removeItem.forEach((button) => {
//   button.addEventListener("click", rmItem);
// });

let update = (id) => {
  let search = basket.find((x) => x.id === id);
  document.getElementById(id).innerHTML = search.item;
  calculation();
};

let clearCart = () => {
  basket = [];
  calculation();
  localStorage.setItem("data", JSON.stringify(basket));
};

clCart.forEach((input) => {
  input.addEventListener("click", clearCart);
  console.log(basket);
});

let increment = (id) => {
  let selectedItem = id;
  let search = basket.find((x) => x === selectedItem);

  if (search === undefined) {
    basket.push({
      id: selectedItem,
      item: 1,
    });
  } else {
    search.item += 1;
  }

  update(selectedItem);
  localStorage.setItem("data", JSON.stringify(basket));
};

function cartClick() {
  let button = this;
  button.classList.add("clicked");
  // if (basket.some((e) => e.id === this.id)) {
  //   console.log("Already in");
  // } else {
  increment(this.id);
  calculation();
  console.log(basket);
  // }
}

// let decrement = (id) => {
//   let selectedItem = id;
//   let search = basket.find((x) => x.id === selectedItem.id);

//   if (search === undefined) return;
//   else if (search.item === 0) return;
//   else {
//     search.item -= 1;
//   }

//   update(selectedItem.id);
//   basket = basket.filter((x) => x.item !== 0);
//   localStorage.setItem("data", JSON.stringify(basket));
// };

let calculation = () => {
  let cartIcon = document.getElementById("cartAmount");
  cartIcon.innerHTML = basket.length;
};

// let rmItem = (id) => {
//   let selectedItem = id;
//   basket = basket.filter((x) => x.id !== selectedItem.id);
//   calculation();
//   localStorage.setItem("data", JSON.stringify(basket));
// };

calculation();

// $.ajax({
//   url: "/cart_fetch",
//   data: JSON.stringify(basket),
//   type: "POST",
//   contentType: "application/json",
//   dataType: "json",
//   success: function (response) {
//     console.log(response);
//   },
//   error: function (error) {
//     console.log(error);
//   },
// });

const menu = document.querySelector("#mobile-menu");
const menuLinks = document.querySelector(".navbar__menu");
const navLogo = document.querySelector("#navbar__logo");

// Display Mobile Menu
const mobileMenu = () => {
  menu.classList.toggle("is-active");
  menuLinks.classList.toggle("active");
};

menu.addEventListener("click", mobileMenu);

// Show active menu when scrolling
const highlightMenu = () => {
  const elem = document.querySelector(".highlight");
  const homeMenu = document.querySelector("#home-page");
  const aboutMenu = document.querySelector("#about-page");
  const servicesMenu = document.querySelector("#services-page");
  let scrollPos = window.scrollY;
  // console.log(scrollPos);

  // adds 'highlight' class to my menu items
  if (window.innerWidth > 960 && scrollPos < 600) {
    homeMenu.classList.add("highlight");
    aboutMenu.classList.remove("highlight");
    return;
  } else if (window.innerWidth > 960 && scrollPos < 1400) {
    aboutMenu.classList.add("highlight");
    homeMenu.classList.remove("highlight");
    servicesMenu.classList.remove("highlight");
    return;
  } else if (window.innerWidth > 960 && scrollPos < 2345) {
    servicesMenu.classList.add("highlight");
    aboutMenu.classList.remove("highlight");
    return;
  }

  if ((elem && window.innerWIdth < 960 && scrollPos < 600) || elem) {
    elem.classList.remove("highlight");
  }
};

window.addEventListener("scroll", highlightMenu);
window.addEventListener("click", highlightMenu);

//  Close mobile Menu when clicking on a menu item
const hideMobileMenu = () => {
  const menuBars = document.querySelector(".is-active");
  if (window.innerWidth <= 768 && menuBars) {
    menu.classList.toggle("is-active");
    menuLinks.classList.remove("active");
  }
};

menuLinks.addEventListener("click", hideMobileMenu);
navLogo.addEventListener("click", hideMobileMenu);

// Cart Page

// let ShoppingCart = document.getElementById("shopping-cart");
// let label = document.getElementById("label");

// let generateCartItems = () => {
//   if (basket.length !== 0) {
//     return (ShoppingCart.innerHTML = basket
//       .map((x) => {
//         let { id, item } = x;
//         let search = shopItemsData.find((x) => x.id === id) || [];
//         let { img, price, name } = search;
//         return `
//       <div class="cart-item">
//         <img width="100" src=https://covers.openlibrary.org/b/isbn/${isbn}-M.jpg alt="" />

//         <div class="details">

//           <div class="title-price-x">
//             <h4 class="title-price">
//               <p>${name}</p>
//               <p class="cart-item-price">$ ${price}</p>
//             </h4>
//             <i onclick="removeItem(${id})" class="bi bi-x-lg"></i>
//           </div>

//           <div class="cart-buttons">
//             <div class="buttons">
//               <i onclick="decrement(${id})" class="bi bi-dash-lg"></i>
//               <div id=${id} class="quantity">${item}</div>
//               <i onclick="increment(${id})" class="bi bi-plus-lg"></i>
//             </div>
//           </div>

//           <h3>$ ${item * price}</h3>

//         </div>
//       </div>
//       `;
//       })
//       .join(""));
//   } else {
//     ShoppingCart.innerHTML = "";
//     label.innerHTML = `
//     <h2>Cart is Empty</h2>
//     <a href="index.html">
//       <button class="HomeBtn">Back to Home</button>
//     </a>
//     `;
//   }
// };

// generateCartItems();

// let update = (id) => {
//   let search = basket.find((x) => x.id === id);
//   document.getElementById(id).innerHTML = search.item;
//   calculation();
//   TotalAmount();
// };

// let removeItem = (id) => {
//   let selectedItem = id;
//   basket = basket.filter((x) => x.id !== selectedItem.id);
//   calculation();
//   generateCartItems();
//   TotalAmount();
//   localStorage.setItem("data", JSON.stringify(basket));
// };

// let TotalAmount = () => {
//   if (basket.length !== 0) {
//     let amount = basket
//       .map((x) => {
//         let { id, item } = x;
//         let filterData = shopItemsData.find((x) => x.id === id);
//         return filterData.price * item;
//       })
//       .reduce((x, y) => x + y, 0);

//     return (label.innerHTML = `
//     <h2>Total Bill : $ ${amount}</h2>
//     <button class="checkout">Checkout</button>
//     <button onclick="clearCart()" class="removeAll">Clear Cart</button>
//     `);
//   } else return;
// };

// TotalAmount();

// let clearCart = () => {
//   basket = [];
//   generateCartItems();
//   calculation();
//   localStorage.setItem("data", JSON.stringify(basket));
// };
