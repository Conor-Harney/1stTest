var Player=function (x,y,w,h)
{
	this.x=x;
	this.y=y;
	this.width=w;
	this.height=h;
	this.isAlive=true;
	
};


Player.prototype.draw = function()
{
    ctx.fillStyle = rgb(255, 0, 0);
    ctx.fillRect(this.x, this.y, this.width, this.height);

};


Player.prototype.clear = function()
{

};

Player.prototype.move = function(x,y)
{

	this.x = x;
	this.y = y;
	

	
};

//create a moveLeft method in the Player.js<br>
//This should change the player's x value (decide for yourself what the change should be)

Player.prototype.moveLeft = function () {
    //You will need to clear either all or else the relevant part of the canvas before redrawing the square using:
    
    this.x = this.x - 1;
};

Player.prototype.moveRight = function () {
    //You will need to clear either all or else the relevant part of the canvas before redrawing the square using:
    
    this.x = this.x + 1;
};
Player.prototype.moveUp = function () {
    //You will need to clear either all or else the relevant part of the canvas before redrawing the square using:
    
    this.y = this.y - 1;
};
Player.prototype.moveDown = function () {
    //You will need to clear either all or else the relevant part of the canvas before redrawing the square using:
    
    this.y = this.y + 1;
};

//The parameter e is the object you want to check is colliding with the player.
Player.prototype.checkCollision = function (e) {

    var collides = false;

    //do the two bounding boxes overlap?
    if ((this.x < e.x + e.width) &&
    (this.x + this.width > e.x) &&
    (this.y + this.height > e.y) &&
    (this.y < e.y + e.height)) {

        collides = true;

    }

    console.log(collides);

    return collides;
};


