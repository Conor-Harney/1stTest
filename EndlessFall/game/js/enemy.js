var Enemy = function (x, y, w, h) {
    this.x = x;
    this.y = y;
    this.width = w;
    this.height = h;
    this.isAlive = true;
    this.speed = 2;
};



Enemy.prototype.dead = function () {

    this.y = 900;
    this.x = (Math.random() * 100000) % 1200;
};

Enemy.prototype.draw = function () {

    ctx.fillStyle = rgb(255, 0, 0);
    ctx.fillRect(this.x, this.y, this.width, this.height);
};

Enemy.prototype.clear = function () {

};

Enemy.prototype.update = function () {
    if (this.y <= 0) {
        this.dead();
    }


};

Enemy.prototype.checkGoal = function (e) {
    if ((this.y > e.y + 50) ){

        this.isAlive = false;

    }
}

Enemy.prototype.getAlive = function () {
    return this.isAlive;
}

Enemy.prototype.move = function (p, fall) {

    this.y -= fall;

    distance = Math.sqrt((this.x - p.x) * (this.x - p.x) + (this.y - p.y) * (this.y - p.y));

    if (distance <= 300) {
        if (this.y < p.y) {
            this.y += this.speed + fall;
            if (this.x <= p.x) {
                this.x += this.speed;
            }
            else {
                this.x -= this.speed;
            }
        }
    }
};
