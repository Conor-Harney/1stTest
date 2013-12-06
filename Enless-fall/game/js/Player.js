var Player = function (x, y, w, h) {
    this.x = x;
    this.y = y;
    this.width = w;
    this.height = h;
    this.isAlive = true;
    this.lives = 3;
    this.score = 0;
};

Player.prototype.draw = function () {

    ctx.save();
    //add in your own colour
    ctx.fillStyle = '#00f';
    ctx.font = 'italic 20px sans-serif';
    ctx.textBaseline = 'top';
    ctx.fillText('Lives: ' + this.lives, 0, 0);
    ctx.fillText('score: ' + (this.score * 100), 100, 0);
    //Any idea what save and restore do?
    ctx.restore();
    ctx.fillStyle = rgb(0, 255, 0);
    ctx.fillRect(this.x, this.y, this.width, this.height);
};

Player.prototype.checkCollision = function (e) {

    var collides = false;

    //do the two bounding boxes overlap?
    if ((this.x < e.x + 50) &&
        (this.x + 50 > e.x) &&
        (this.y + 40 > e.y) &&
        (this.y < e.y + 40)) {

        collides = true;

    }

    return collides;
};

Player.prototype.increaseLives = function () {
    this.lives++;
}

Player.prototype.increaseScore = function () {
    this.score++;
}

Player.prototype.decreaseLife = function () {
    if (this.lives > 0) {
        this.lives--;
    }
}

Player.prototype.update = function () {
    
    if (KeyController.isKeyDown(Key.LEFT)) {
        this.moveLeft();
    }
    if (KeyController.isKeyDown(Key.RIGHT)) {
        this.moveRight();
    }
    if (KeyController.isKeyDown(Key.UP)) {
        this.moveUp();
    }
    if (KeyController.isKeyDown(Key.DOWN)) {
        this.moveDown();
    }
    
}




Player.prototype.clear = function()
{

};

Player.prototype.move = function(x,y)
{
	this.x = x;
	this.y = y;
};


Player.prototype.moveLeft = function () {

    this.x -= 5;

}

Player.prototype.moveRight = function () {

    this.x += 5;

}

Player.prototype.moveUp = function () {

    this.y -= 5;

}

Player.prototype.moveDown = function () {

    this.y += 5;

}

