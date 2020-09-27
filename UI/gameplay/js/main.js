   
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

    // var joystick = nipplejs.create({
    //     zone: document.getElementById('static'),
    //     mode: 'static',
    //     position: {left: '25%', top: '50%'},
    //     color: 'red',
    //     size: 600,
    //     shape: 'square'
    // });

    // let moving = {
    //     center: true,
    //     up: false,
    //     down: false,
    // }

    // joystick.on('start end', function(evt, data) {
    //     // dump(evt.type);
    //     //console.log('event ::',evt.type);
    //     if(evt.type === 'end'){
    //         moving = {
    //             center: true,
    //             up: false, 
    //             down: false
    //         }
    //     }
    //   }).on('move', function(evt, data) {
    //     // console.log('move event ::',data);
    //     if(data.distance <= 75 && moving){
    //         moving = {
    //             center: true, 
    //             up: false,
    //             down: false
    //         }
    //     }
    //   }).on('plain:up  plain:down',
    //   function(evt, data) {
    //       console.log('data ', evt.type)
    //     if(evt.type === 'plain:up'){
    //         moving = {
    //             center: false,
    //             up: true,
    //             down: false,
    //         };
    //     }
    //     else if (evt.type === 'plain:down'){
    //         moving = {
    //             center: false,
    //             up: false,
    //             down: true,
    //         };
    //     }
    //   }
    //        ).on('pressure', function(evt, data) {
    //     // debug({
    //     //   pressure: data
    //     // });
    //   });
    
    
    // setInterval(function(){ 
    //     // console.log('movement state ', moving);
    //     if(moving.center === true){
    //         console.log('event type center');
    //         triggerUE4EventMap('moveEvent', `dir:center`);
    //     }
    //     else if(moving.up === true){
    //         console.log('event type up');
    //         triggerUE4EventMap('moveEvent', `dir:up`);
    //     }
    //     else if(moving.down === true){
    //         console.log('event type down');
    //         triggerUE4EventMap('moveEvent', `dir:down`);
    //     }
    // }, 50);

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