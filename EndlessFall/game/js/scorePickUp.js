var scorePickUp = function(posXIn, posYIn){

    this.worldPosX = (Math.random() * 100000) % 1100;
	this.worldPosY = posYIn;//the position in the world
	this.relScreenPosX = this.worldPosX;
	this.relScreenPosY =  this.worldPosY;
	this.screenPositionY = 0;
	this.size = 50;
	this.alive = true;
	this.scoreValue = 1;
};

scorePickUp.prototype.update = function(screenPosX, screenPosY){
	if(this.alive == true){
		this.relScreenPosX = this.worldPosX + screenPosX;
		this.relScreenPosY = this.worldPosY + screenPosY;
		this.screenPositionY = screenPosX;
	}
	if (this.relScreenPosY < 0){this.destroy();}
};

scorePickUp.prototype.getPosition = function(){
	if(this.alive == true){
		return this.relScreenPosX, this.relScreenPosY;
	}
};

scorePickUp.prototype.destroy = function () {
    this.worldPosY = this.worldPosY + 800;
    this.worldPosX = (Math.random() * 100000) % 1100;
};

scorePickUp.prototype.checkCollision = function(playersPositionX, playersPositionY, playerSizeX, playerSizeY){
	if(this.alive == true){
		if(playersPositionX > this.relScreenPosX + this.size ||
			playersPositionX + playerSizeX < this.relScreenPosX ||
			playersPositionY > this.relScreenPosY + this.size ||
			playersPositionY + playerSizeY < this.relScreenPosY){return false;}
			else{
				this.destroy();
				return this.scoreValue;
			}
	}			
};


scorePickUp.prototype.draw = function()
{
	if(this.alive == true)
	{
		var img = AM.cache["images/scorePack.png"];
		ctx.drawImage(img, this.relScreenPosX, this.relScreenPosY, this.size, this.size);
	}
};