function generateArt() {
	var width_input = document.getElementById("width-input").value;
	var height_input = document.getElementById("height-input").value;
	var no_colors_input = document.getElementById("no-colors-input").value;
	var output = document.getElementById("generated-image");
	var download_link = document.getElementById("download-image");
	var image_colors = document.getElementById("image-colors");
	var canvas = document.createElement("canvas");

	canvas.width = width_input;
	canvas.height = height_input;
	var ctx = canvas.getContext("2d");

	// Create gradient
	var grd = ctx.createLinearGradient(0, height_input/2, width_input, height_input/2);
	let colors = [];
	if(no_colors_input > 1) {
		for(var i = 0; i < no_colors_input; i++) {
			var r = getRandomInt(255);
			var g = getRandomInt(255);
			var b = getRandomInt(255);
			var rgb = "rgb(" + r + "," + g + "," + b + ")";
			grd.addColorStop(i/(no_colors_input-1), rgb);
			colors.push(rgb);
		}
	}
	else {
		var r = getRandomInt(255);
		var g = getRandomInt(255);
		var b = getRandomInt(255);
		var rgb = "rgb(" + r + "," + g + "," + b + ")";
		grd.addColorStop(0, rgb);
		colors.push(rgb);
	}
	
	// Fill with gradient
	ctx.fillStyle = grd;
	ctx.fillRect(0, 0, width_input, height_input);

	var url = canvas.toDataURL();

	var a = document.createElement('a');
	a.download = 'random-art.png';
	a.href = url;
	a.textContent = 'Download PNG';

	output.src = url;
	download_link.innerHTML = '';
	download_link.appendChild(a);
	image_colors.innerHTML = '';
	for(var i = 0; i < colors.length; i++)
		image_colors.innerHTML += (colors[i] + "<br>");
}

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}