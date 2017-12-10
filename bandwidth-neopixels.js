var express = require('express');
var app = express();
var http = require('http');
var server = http.Server(app);
var tomatoBandwidth = require('tomato-router-bandwidth');

const port = 81;
var lastReading = {};

var tomatoOptions = {
	username: 'admin', //required
	password: 'password', //required
	_http_id: 'your_http_id', //required
	callback: (result) =>{
		if(result.error){
			console.log('Error: ', result.error);
		}else{
		    lastReading = {
		        down: result.bandwidth.MbitsDown,
		        up: result.bandwidth.MbitsUp
		    };
		}
		setTimeout(pollBandwidth, 500);
	}
};

pollBandwidth();

function pollBandwidth(){
    tomatoBandwidth(tomatoOptions);
}

app.get('/', function(req,res){
    res.status(200).send(lastReading);
});

server.listen(port, function(){
    console.log('Bandwidth webserver started on port '+port);
});