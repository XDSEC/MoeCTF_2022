var sx = document.querySelector('#sx');
var yw = document.querySelector('#yw');
var wy = document.querySelector('#wy');
var zh = document.querySelector('#zh');
var zf = document.querySelector('#zf');
var arr = [sx, yw, wy, zh];
var flag = false;
function check() {
    if (flag == true) {
        clearInterval(timer);
    }
    var sum = 0;
    for (var i = 0; i < arr.length; i++) {
        sum += eval(arr[i].innerHTML);
    }
    if (sum == eval(zf.innerHTML) && sum > 600) {
        alert('moectf{this_is_a_fake_flag}');
        flag = true;
    }
}
var timer = setInterval(check, 1000);




