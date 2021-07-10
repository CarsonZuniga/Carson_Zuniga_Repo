function generateArt() {
	var width_input = document.getElementById("width-input").value;
	var height_input = document.getElementById("height-input").value;
	var output = document.getElementById("generated-image");
	var download_link = document.getElementById("download-image");
	var canvas = document.createElement("canvas");

	canvas.width = width_input;
	canvas.height = height_input;
	var ctx = canvas.getContext("2d");

	// Create gradient
	var grd = ctx.createLinearGradient(0, height_input/2, width_input, height_input/2);
	grd.addColorStop(0, "rgb(" + getRandomInt(255) + "," + getRandomInt(255) + "," + getRandomInt(255)+")");
	grd.addColorStop(1, "rgb(" + getRandomInt(255) + "," + getRandomInt(255) + "," + getRandomInt(255)+")");

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
}

function getRandomInt(max) {
  return Math.floor(Math.random() * max);
}