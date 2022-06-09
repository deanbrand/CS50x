let basket = [
  { id: "10324", item: 1 },
  { id: "1697", item: 1 },
  { id: "10324", item: 1 },
  { id: "1697", item: 1 },
  { id: "1462", item: 1 },
  { id: "10324", item: 1 },
  { id: "1697", item: 1 },
  { id: "307", item: 1 },
  { id: "307", item: 1 },
];

// for (i = 0; i < basket.length; i++) {
//   if ("10324" in basket) {
//     console.log("Already in");
//   }
// }

if (basket.some((e) => e.id === "10324")) {
  console.log("Already in");
}