   
//#region BINDING

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
    var posPan = document.getElementById('pos-rec');

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
        bindings.message = "test";
        console.log('bind ', gameplay.message);
        onSteal();
        console.log('stealButton ', ev.type);
    });

    // We create a manager object, which is the same as Hammer(), but without the presetted recognizers. 
    var mcBlock= new Hammer(blockButton);

    mcBlock.on("tap", function(ev) {
        onBlock();
        console.log('blockButton ', ev.type);
    });


    // create a simple instance
    // by default, it only adds horizontal recognizers
    var mcPos = new Hammer(posPan);

    // let the pan gesture support all directions.
    // this will block the vertical scrolling on a touch-device while on the element
    mcPos.get('pan').set({ direction: Hammer.DIRECTION_ALL });

    // listen to events...
    mcPos.on("panup pandown panend", function(ev) {
        onPan(ev.type);
        console.log('PosRec ', ev.type);
    });

    function onPan(direction) {
        triggerUE4EventMap('moveEvent', `PanDirection:${direction}`, 'Hitpoints:98',);
    }

    function onShootStart() {
        triggerUE4EventMap('shootStartEvent', 'ItemID:12', 'Hitpoints:98',);
    }

    function onShootEnd() {
        triggerUE4EventMap('shootEndEvent', 'ItemID:12', 'Hitpoints:98',);
    }

    function onSteal() {
        triggerUE4EventMap('stealEvent', 'ItemID:12', 'Hitpoints:98',);
    }
    
    function onBlock() {
        triggerUE4EventMap('blockEvent', 'ItemID:12', 'Hitpoints:98',);
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