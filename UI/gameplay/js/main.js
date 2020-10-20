   
//#region BINDING
    let centered = true;

    let gameplay = {
        homeScore: 0,
        awayScore: 0,
        message: "",
    };

    let bindings = $.bindings(gameplay);

//#endregion BINDING

//#region UI CONTROLS 

    var shootButton = document.getElementById('shoot-button');
    var stealButton = document.getElementById('steal-button');
    var blockButton = document.getElementById('block-button');

    var Joy1 = new JoyStick('joyDiv',{
        internalFillColor: 'rgba(24,24,28,0.15)',
        internalStrokeColor: 'rgba(24,24,28,0.15)',
        externalStrokeColor: 'rgba(24,24,28,0.15)'
    });

    setInterval(function(){ 
        
        let dir = Joy1.GetDir(); 
        triggerUE4EventMap('moveEvent', `PanDirection:${dir}`);

    }, 50);


    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcShoot = new Hammer(shootButton);

    mcShoot.on("press", function(ev) {
        onShootStart();
        console.log('shootbutton ', ev.type);
    });

    mcShoot.on("pressup", function(ev) {
        onShootEnd();
        console.log('shootbutton ', ev.type);
    });

    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcSteal= new Hammer(stealButton);

    mcSteal.on("tap", function(ev) {
        onSteal();
        console.log('stealButton ', ev.type);
    });

    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcBlock= new Hammer(blockButton);

    mcBlock.on("tap", function(ev) {
        onBlock();
        console.log('blockButton ', ev.type);
    });

    function onPan(direction) {
        triggerUE4EventMap('moveEvent', `PanDirection:${direction}`);
    }

    function onShootStart() {
        triggerUE4EventMap('shootStartEvent');
    }

    function onShootEnd() {
        triggerUE4EventMap('shootEndEvent');
    }

    function onSteal() {
        triggerUE4EventMap('stealEvent');
    }
    
    function onBlock() {
        triggerUE4EventMap('blockEvent');
    }

//#endregion UI CONTROLS

//#region UE4 EVENTS
    function updateScore(home, away){
        bindings.homeScore = home;
        bindings.awayScore = away;
    }

    function displayMessage(message){
        bindings.message = message;
    }

    function clearMessage(){
        bindings.message = "";
    }
//#endregion