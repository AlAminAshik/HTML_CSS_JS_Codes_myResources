function Addnumbers() {
    let a = document.getElementById("num1").value;
    let b = document.getElementById("num2").value;
    let sum = parseFloat(a) + parseFloat(b);

    document.getElementById("result").value = "The sum is: " + sum;
    console.log(sum);
}

function Multnumbers() {
    let a = document.getElementById("num1").value;
    let b = document.getElementById("num2").value;
    let product = parseFloat(a) * parseFloat(b);
    
    document.getElementById("result").value = "The product is: " + product;
    console.log(product);
}