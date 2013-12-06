var Menu = function (x, y, w, h) {
    this.x = x;
    this.y = y;
    this.width = w;
    this.height = h;

    this.gamex = this.width / 2;
    this.gamey = this.height / 2;
    this.gameWidth = 100;
    this.gameHeight = 50;
    this.isAlive = true;
    this.mousePosx;
    this.mousePosy;
};

Menu.prototype.draw = function () {

    if (this.isAlive == true) {
        ctx.fillStyle = rgb(0, 255, 0);
        ctx.fillRect(this.x, this.y, this.width, this.height);
        ctx.fillStyle = rgb(255, 255, 0);
        ctx.fillRect(this.gamex, this.gamey, this.gameWidth, this.gameHeight);
        ctx.save();
        //add in your own colour
        ctx.fillStyle = '#00f';
        ctx.font = 'italic 30px sans-serif';
        ctx.textBaseline = 'top';
        ctx.fillText('Main menu', this.width / 2, 100);
        //Any idea what save and restore do?

        //add in your own colour
        ctx.fillStyle = '#00f';
        ctx.font = 'italic 30px sans-serif';
        ctx.textBaseline = 'top';
        ctx.fillText('x: ' + this.mousePosx + ' y: ' + this.mousePosy, 300, 100);
        //Any idea what save and restore do?
        ctx.restore();
    }

};

Menu.prototype.checkCollision = function (ex, ey) {


    this.mousePosx = ex;
    this.mousePosy = ey;
    //do the two bounding boxes overlap?
    if ((this.gamex < ex) &&
        (this.gamex + this.gameWidth > ex) &&
        (this.gamey + this.gameHeight > ey) &&
        (this.gamey < ey)) {

        this.isAlive = false;

    }

};



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
