
var Goal = function (x, y, w, h) {
    this.x = x;
    this.y = y;
    this.width = w;
    this.height = h;
    this.isAlive = true;

};


Goal.prototype.draw = function () {


    ctx.fillStyle = rgb(0, 225, 225);
    ctx.fillRect(this.x, this.y, this.width, this.height);

};


Goal.prototype.clear = function () {

};

Goal.prototype.move = function (y) {
    
    this.y -= y;
};
