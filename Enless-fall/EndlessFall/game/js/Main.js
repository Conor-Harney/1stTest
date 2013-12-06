var AM;
var game;
function main()
{
	AM = new AssetManager;
	AM.queueDownload("images/healthPack.png");
	AM.queueDownload("images/scorePack.png");
	AM.downloadAll(setup);
	
	
			
}

function setup() {
    console.log("version 1");
	this.game= new Game();

	this.game.initCanvas();
	ctx.clearRect(0, 0, canvas.width, canvas.height);
	

	this.game.initWorld();	
	this.game.gameLoop();	
}
