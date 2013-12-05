var player, b_gameOver, healthPack1, scorePack1, viewportPosY, cameraSpeed;
//These are global variables and are NOT recommended because they cause bad things to happen
//Some refactoring will be needed...

var canvas, ctx;
var R = 10;
var G = 0;
var B = 0;

function Game ()
{
	this.viewportPosY = 200;
	this.score = 0;
	this.cameraSpeed = 0.1;
}

Game.prototype.initWorld = function () {


    this.player = new Player(100, 100, 50, 40);
    this.goal = new Goal(0, 8000, 50, 40);
    this.e = new Enemy(300, 100, 50, 40);
    canvas.addEventListener("mousedown", doMouseDown, false);
    this.gameWon = false;
    this.gameOver = false;
    this.b_gameOver = false;
	this.healthPack1 = new healthPickUp(200, 200);
    this.scorePack1 = new scorePickUp(50, 300);
	playBackgroundLoop();

	//gameLoop();
     //window.requestAnimFrame(game.gameLoop);
}

function doMouseDown(event) {

    if (event.which === 1) {
        play();
    }
    if (event.which === 2) {
        play();
    }
    if (event.which === 3) {
        play();
    }

}

Game.prototype.initCanvas=function () { 

	canvas = document.createElement('canvas'); 
	ctx = canvas.getContext('2d'); 

	document.body.appendChild(canvas);
	//set canvas to size of the screen.
	canvas.width = window.innerWidth; 
	canvas.height = window.innerHeight;
}

function play() {
//    var laser = document.getElementById("gameSound");
//    laser.play();

    //another way of playing audio
    var boom = new Audio("boop-3.wav");
    boom.play();
}

function loopPlay() {
    var b = new Audio("boop-3.wav");
    b.addEventListener('ended', function () {
        this.currentTime = 0;
        this.play();
    }, false);

    b.play();
}

Game.prototype.update = function () {

    if (this.gameWon == false && this.gameOver == false) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        if (this.e.getAlive() == true && this.player.isAlive == true) {
            this.e.move(this.player, 1);

            this.e.update();
            this.e.checkGoal(this.goal);
        }
        this.goal.move(1);


        if (this.player.checkCollision(this.goal) == true) {

            this.collisionResponse();

        }

        if (this.player.checkCollision(this.e) == true && this.e.isAlive == true) {
            this.e.dead();
            this.player.decreaseLife();
        }

        if (this.player.isAlive == true) {

            this.player.update();

        }
        if (this.player.lives == 0) {
            this.player.isAlive = false;
            this.gameOver = true;
            ctx.save();
            //add in your own colour
            ctx.fillStyle = '#00f';
            ctx.font = 'italic 30px sans-serif';
            ctx.textBaseline = 'top';
            ctx.fillText('Game Over you failed to fall', 200, 100);
            //Any idea what save and restore do?
            ctx.restore();
        }

        if(this.cameraSpeed < 2){
            this.cameraSpeed += 0.001;
        }
        var healthAdder = this.healthPack1.checkCollision(this.player.x, this.player.y, this.player.width, this.player.height);
        if (healthAdder != false) { this.player.increaseLives(); }
        this.viewportPosY = this.viewportPosY - this.cameraSpeed;
        this.healthPack1.update(0, this.viewportPosY);
        healthAdder = false;

         var scoreAdder = this.scorePack1.checkCollision(this.player.x, this.player.y, this.player.width, this.player.height);
        if (scoreAdder != false) { this.player.increaseScore(); }
        this.viewportPosY = this.viewportPosY - this.cameraSpeed;
        this.scorePack1.update(0, this.viewportPosY);
        scoreAdder = false;
    }
}

Game.prototype.collisionResponse = function () {
    this.gameWon = true;
    ctx.save();
    //add in your own colour
    ctx.fillStyle = '#00f';
    ctx.font = 'italic 30px sans-serif';
    ctx.textBaseline = 'top';
    ctx.fillText('You win!!!!!!!!!!!!!!!!!!', 300, 100);
    //Any idea what save and restore do?
    ctx.restore();
}


Game.prototype.gameLoop = function () {
    game.update();
    game.draw();

    window.requestAnimFrame(game.gameLoop);
}

Game.prototype.draw = function (ctx) {
    this.goal.draw();
    if (this.player.isAlive == true) {
        this.player.draw();
    }

    if (this.e.isAlive == true) {
        this.e.draw();
    }

    this.healthPack1.draw();
    this.scorePack1.draw();
}