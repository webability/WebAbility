
/*
    editorElement.js, WAJAF, the WebAbility(r) Javascript Application Framework
    Contains an editor to create masks
    (c) 2014 Philippe Thomassigny

    This file is part of DOMMASK

    DOMMASK is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    DOMMASK is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with DOMMASK.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Known code.attributes of element:
   * type, id
   * left, top, anchorleft, anchortop, width, height
   * display           default display: ''
   * style
   * classname         default class: button

   * value            string, content of the button
   * action           string, type of button
                      known actions: '' (empty string) simple button
                      Others: confirm, cancel, info, insert, update, delete, view, clear, reset, submit, previous, next, first, last
   * link             name of group container to register the element
   * status           default status of the button: '' or 'disabled'
*/

WA.Elements.editorElement = function(domNodeFather, domID, code, listener)
{
  var self = this;
  code.domtype = 'editor'; // IE bug on input type, we force the type at the node creation
  WA.Elements.editorElement.sourceconstructor.call(this, domNodeFather, domID, code, 'div', { classname:'editor' }, listener);

  this.status = 1; // new, 2 = modified, 3 = saved
  this.nodes = [];

  this.menu = new WA.Elements.editorElement.menucontainer(this);
  this.elements = new WA.Elements.editorElement.elementcontainer(this);
  this.sandbox = new WA.Elements.editorElement.sandboxcontainer(this);
  this.params = new WA.Elements.editorElement.paramscontainer(this);
  
  this.addEvent('start', start);
  this.addEvent('stop', stop);
  this.addEvent('resize', this.resize);

  /*
  function click()
  {
    var n = new WA.Elements.editorElement.elementelement(self.sandbox.domNode, 'group');
    self.nodes.push(n);
  }
  */
  
  function start()
  {
    self.menu.start();
    self.elements.start();
    self.sandbox.start();
    self.params.start();
  }

  function stop()
  {
//    WA.Managers.event.off('click', self.domNode, click, false);
  }

  this.createElement = createElement;
  function createElement(type)
  {
    self.sandbox.createElement(type);
  }
  
  this.menuAction = menuAction; 
  function menuAction(type)
  {
    switch(type)
    {
      case 'save': save(); break;
      case 'run': run(); break;
    
    }
  }

  this.createParams = createParams;
  function createParams(data, listener)
  {
    self.params.createParams(data, listener);
  }

  function save()
  {
    // get the full object and send it to server with ajax
    var data = self.sandbox.save();
    jsondata = WA.JSON.encode(data);
    
    var request = WA.Managers.ajax.createRequest(WA.Managers.wa4gl.url + WA.Managers.wa4gl.prelib + self.app.applicationID + WA.Managers.wa4gl.premethod + self.id + WA.Managers.wa4gl.preformat + WA.Managers.wa4gl.format, 'POST', 'Order=save', datasaved, false);
    request.addParameter('name', self.sandbox.name);
    request.addParameter('data', jsondata);
    request.send();

    // xdomID[1] is the version of our app and the id of the tab
    var ct = WA.$N('main|single|application');
    ct.setTitle('appmask_'+self.xdomID[0]+'_'+self.xdomID[1], self.sandbox.name);
    /*
    main|single|appmask_mask_new_1_selector
    
    var ldomID = WA.parseID(id, self.xdomID);
    if (!ldomID)
      throw 'Error: the zone id is not valid in tabContainer.createZone: id=' + domID;
    // check the zone does not exists YET !
    if (self.zones[ldomID[2]])
      throw 'Error: the zone already exists in tabContainer.createZone: id=' + ldomID[2];

    // 1. call event precreate, can we create ?
    if (!self.callEvent('precreate', {id:ldomID[2]}))
      return null;
*/



  }
  
  function datasaved(request)
  {
    alert(request.responseText);
  }
  
  function run()
  {
    var ct = WA.$N('main|single|application');
    var nodeName = 'apprunmask_' + self.sandbox.name;
    var node = ct.app.getNode(nodeName);
    if (!node)
    {
      var tree = {tag:'zone',attributes:{id:nodeName,title:nodeName,closeable:'yes',moveable:'yes',application:'run|code',params:'name='+self.sandbox.name}};
      ct.app.createTree('application', tree);
    }
    ct.app.getNode('application').activateZone(nodeName);
  
/*  
    // get the full object and send it to server with ajax
    var request = WA.Managers.ajax.createRequest(WA.Managers.wa4gl.url+'?P=run.code.json', 'POST', null, runcalled, false);
    request.addParameter('name', self.sandbox.name);
    request.send();
*/
  }

  function runcalled(request)
  {
  
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    WA.Elements.editorElement.source.destroy.call(self, fast);
    self = null;
  }

}

// Add basic element code
WA.extend(WA.Elements.editorElement, WA.Managers.wa4gl._element);

WA.Elements.editorElement.menucontainer = function(main)
{
  var self = this;
  this.main = main;
  this.options = {};
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'menu';
  main.domNode.appendChild(this.domNode);
 
  this.start = start; 
  function start()
  {
    self.options.save = new WA.Elements.editorElement.menuelement(this, 'save');
    self.options.run = new WA.Elements.editorElement.menuelement(this, 'run');
  }
  
  this.menuAction = menuAction; 
  function menuAction(type)
  {
    self.main.menuAction(type);
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}

WA.Elements.editorElement.elementcontainer = function(main)
{
  var self = this;
  this.main = main;
  this.options = {};
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'element';
  main.domNode.appendChild(this.domNode);

  this.start = start; 
  function start()
  {
    self.options.group = new WA.Elements.editorElement.elementelement(this, 'group');
    self.options.text = new WA.Elements.editorElement.elementelement(this, 'text');
    self.options.textarea = new WA.Elements.editorElement.elementelement(this, 'textarea');
    self.options.lov = new WA.Elements.editorElement.elementelement(this, 'lov');
    self.options.hidden = new WA.Elements.editorElement.elementelement(this, 'hidden');
    self.options.button = new WA.Elements.editorElement.elementelement(this, 'button');
  }

  this.createElement = createElement; 
  function createElement(type)
  {
    self.main.createElement(type);
  }

  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}

WA.Elements.editorElement.sandboxcontainer = function(main)
{
  var self = this;
  this.main = main;
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'sandbox';
  main.domNode.appendChild(this.domNode);

  this.name = 'mask1';
  this.elements = [
    { 'element': new WA.Elements.editorElement.sandboxelement(this, this, 'group'),
      'children': []
    }
  ];
  
  function click(event)
  {
    // create parameters based on the element type, and fill them with the local element
    // the general form elements
    self.main.createParams(
      { 'name': { id:'name', type:'text', title: 'Mask name/id:', value: self.name }
      },
      listenerparams
    );
    return WA.browser.cancelEvent(event);
  }

  this.clickelement = clickelement;
  function clickelement(event, data, listener)
  {
    // create parameters based on the element type, and fill them with the local element
    // the general form elements
    self.main.createParams(data, listener);
    return WA.browser.cancelEvent(event);
  }
  
  function listenerparams(param, value)
  {
    // called when any params change occurs
    if (param == 'name')
      self.name = value;
  }
  
  function builddata(object)
  {
    var data = [];
    for (var i = 0, j = object.length; i<j; i++)
    {
      var dx = { 'element': object[i].element.save(),
                 'children': object[i].children?builddata(object[i].children):null
               };
      data.push(dx);
    }
    return data;
  }
  
  this.save = save;
  function save()
  {
    return builddata(self.elements);
  }
  
  this.start = start; 
  function start()
  {
    WA.Managers.event.on('click', self.domNode, click, false);
  }
  
  this.createElement = createElement; 
  function createElement(type)
  {
    // agrega al primer groupContainer
    self.elements[0].children.push( { 'element': new WA.Elements.editorElement.sandboxelement(self, self.elements[0].element, type), 'children': null } );
  }

  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}

WA.Elements.editorElement.paramscontainer = function(main)
{
  var self = this;
  this.main = main;
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'params';
  main.domNode.appendChild(this.domNode);
  
  this.listener = null;
  this.elements = null;

  this.start = start; 
  function start()
  {
  }
  
  this.createParams = createParams;
  function createParams(data, listener)
  {
    // 1. unlink old params if any
    if (self.listener)
      self.listener.call(self, '::system', 'unlink');
    if (self.elements)
    {
      for (var i in self.elements)
      {
//        self.elements[i].stop();
        self.elements[i].destroy();
      }
    }
    self.elements = null;

    // 2. link new params
    self.listener = listener;

    self.elements = {};
    for (var i in data)
    {
      // crea los parametros
      var d = new WA.Elements.editorElement.paramelement(self, data[i], listener);
      self.elements[i] = d;
    }
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}

/* elements of each container */

WA.Elements.editorElement.menuelement = function(container, type)
{
  var self = this;
  this.main = container;
  this.type = type;
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'button menuelement_'+type;
  this.domNode.innerHTML = type;
  container.domNode.appendChild(this.domNode);

  WA.Managers.event.on('click', this.domNode, click, false);
  
  function click(event)
  {
    self.main.menuAction(self.type);
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}


WA.Elements.editorElement.elementelement = function(container, type)
{
  var self = this;
  this.main = container;
  this.type = type;
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'button element_'+type;
  this.domNode.innerHTML = type;
  container.domNode.appendChild(this.domNode);
  
  WA.Managers.event.on('click', this.domNode, click, false);
  
  function click(event)
  {
    self.main.createElement(self.type);
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}

WA.Elements.editorElement.sandboxelement = function(main, container, type)
{
  var self = this;
  this.main = main;
  this.container = container;
  this.type = type;
  this.data = new WA.Elements.editorElement['sandbox'+type+'element']();
  
  this.domNode = document.createElement('div');
  this.domNode.className = 'sbelement_'+type;
  container.domNode.appendChild(this.domNode);

  this.domNodeTitle = document.createElement('div');
  this.domNodeTitle.innerHTML = type;
  this.domNode.appendChild(this.domNodeTitle);
  
  this.element = new WA.Elements.editorElement['sandbox'+type+'element']();
  
  WA.Managers.event.on('click', this.domNode, click, false);
  
  function click(event)
  {
    // create parameters based on the element type, and fill them with the local element
    var fields = {};
    for (var i in self.data.data)
    {
      var f = { id: i, type: 'text', title: i+':', value: self.data.data[i]};
      fields[i] = f;
    }
    return self.main.clickelement(event, fields, listener);
  }
  
  function listener(vart, name)
  {
//    alert(vart + ' ' + name);
  }
  
  this.save = save;
  function save()
  {
    return self.element.data;
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    self = null;
  }
}

WA.Elements.editorElement.sandboxgroupelement = function()
{
  var self = this;
  this.data = {
    type: 'group',
    id:'group_',
    style:'',
    method: 'POST',
    authmodes: {'insert':1, 'update':1, 'delete':1, 'view':1},
    mode: 'insert',
    key: null,
    keyfield: 'key',
    varmode: 'mode',
    varorder: 'order',
    varkey: 'key',
    messages: {
      alertmessage: '',
      servermessage: '',
      titleinsert: '',
      titleupdate: '',
      titledetele: '',
      titleview: '',
      insertok: '',
      updateok: '',
      confirmdelete: '',
      deleteok: ''
      },
    jsonsuccess: '',
    jsonfailure: '',
    phpgetrecord: '',
    phppreinsert: '',
    phpinsert: '',
    phppostinsert: '',
    phppreupdate: '',
    phpupdate: '',
    phppostupdate: '',
    phppredelete: '',
    phpdelete: '',
    phppostdelete: ''
  };
}

WA.Elements.editorElement.sandboxfieldelement = function()
{
  var self = this;
  this.data = {
    type: 'text',
    id:'text_',
    style:'',
    name:'',
    urlvariable:'',
    authmodes: {'insert':1, 'update':1, 'delete':1, 'view':1},
    viewmodes: {'delete':1, 'view':1},
    readonlymodes: {},
    notnullmodes: {},
    disabledmodes: {},
    helpmodes: {'insert':1, 'update':1},
    messages: {
      title: '',
      helptitle: '',
      helpsummary: '',
      helpdescription: '',
      statusok: '',
      statusnotnull: '',
      statusbadformat: '',
      statustooshort: '',
      statustoolong: '',
      statustoofewwords: '',
      statustoomanywords: '',
      statuscheck: ''
      },
    auto:'',
    defaultvalue:'',
    phpcalcfunction:'',
    encoded:false,
    entities:false,
    automessage:'',
    size:0,
    format:'',
    emptyonnull:false,
    nullonempty:false,
    nullvalue:'',
    md5encrypted:false,
    minlength: null,
    maxlength: null,
    minwords: null,
    maxwords: null,
    min: null,
    max: null
  }
}

WA.Elements.editorElement.sandboxtextelement = function()
{
  var self = this;
  this.data = {
    type: 'text',

    format:'',
    emptyonnull:false,
    nullonempty:false,
    nullvalue:'',
    md5encrypted:false,
    minlength: null,
    maxlength: null,
    minwords: null,
    maxwords: null,
    min: null,
    max: null
  };

}

WA.Elements.editorElement.sandboxtextareaelement = function()
{
  var self = this;
  this.data = {
    type: 'textarea',
    width: 400,
    height: 100,
    cols: null,
    lines: null
  };

}

WA.Elements.editorElement.sandboxlovelement = function()
{
/*
  public $RadioButton = false;      // boolean
  public $MultiSelect = false;      // boolean

  public $ListTable = null;         // List DB_Table object
  public $ListKey = null;           // the key field on list
  public $ListName = null;          // the name field on list
  public $ListOrder = null;         // field order by on list
  public $ListWhere = null;         // where object on list
  public $ListSeparator = ' / ';    // separator if the list name is an array
  public $ListEncoded = false;      // boolean true if the list result is encoded
  public $ListEntities = false;     // boolean true if the list result has entities
  public $Controlling = null;       // this LOV controls another LOV (Id of the FIELD)
  public $ControllingOptions = null; // The special options (array( father => array(childs => childs) ) )
  public $ControllingIndex = null;   // the tabindex of the controlled field, used to actualize field validity
  public $OnEvent = null;            // If a DB_MaskField::LOO or DB_MaskField::LOV have a javascript event

  public $MultiSelect = false;       // boolean

  public $options = null;            // array
  
*/
}

WA.Elements.editorElement.sandboxhiddenelement = function()
{

}

WA.Elements.editorElement.sandboxbuttonelement = function()
{
/*
  public $action = 'submit';
  public $OnClick = 'reset();';          // for ButtonFields
  public $ButtonFieldInsert = null;      // string
  public $ButtonFieldUpdate = null;      // string
  public $ButtonFieldDelete = null;      // string
  public $ButtonFieldView = null;        // string
  public $ButtonFieldAsImage = null;     // string link of image
  public $OnEvent = null;
*/
}

WA.Elements.editorElement.paramelement = function(container, data, listener)
{
  var self = this;
  this.main = container;
  this.id = data.id;
  this.type = data.type;
  this.title = data.title;
  this.value = data.value;
  this.listener = listener;
  
  this.domNodeLabel = document.createElement('label');
  this.domNodeLabel.innerHTML = this.title;
  container.domNode.appendChild(this.domNodeLabel);

  this.domNode = document.createElement('input');
  this.domNode.type = this.type;
  this.domNode.value = this.value;
  this.domNode.className = 'paramelement_'+this.type;
  container.domNode.appendChild(this.domNode);

  WA.Managers.event.on('keyup', this.domNode, keyup, false);
  
  function keyup(event)
  {
    var value = self.domNode.value;
    self.listener.call(self, self.id, value);
  }
  
  this.destroy = destroy;
  function destroy(fast)
  {
    WA.Managers.event.off('keyup', self.domNode, keyup, false);
    self.domNodeLabel.parentNode.removeChild(self.domNodeLabel);
    self.domNode.parentNode.removeChild(self.domNode);
    self = null;
  }
}
