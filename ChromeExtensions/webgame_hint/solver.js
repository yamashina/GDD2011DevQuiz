//var element = document.getElementById('card0');
//if (element == null) {
//  alert('Card element is not found. Check element id.');
//} else {
//  var myevent = document.createEvent('MouseEvents');
//  myevent.initEvent('click', false, true);
//  element.dispatchEvent(myevent);
//  alert('Card color is "' + element.style.backgroundColor + '".');
//}

var base;
var i;
for (base=0; base<1024; base++) {
	for (i=0; i<1024; i++) {
		var element = document.getElementById('card'+base);
		if (element == null) {
//		  alert('Card element is not found. Check element id.');
		} else {
		  var myevent = document.createEvent('MouseEvents');
		  myevent.initEvent('click', false, true);
		  element.dispatchEvent(myevent);
		}
	
		if (i == base) {
			i++;
		}
		element = document.getElementById('card'+i);
		if (element == null) {
//		  alert('Card element is not found. Check element id.');
		} else {
		  var myevent = document.createEvent('MouseEvents');
		  myevent.initEvent('click', false, true);
		  element.dispatchEvent(myevent);
		}
	}
}
