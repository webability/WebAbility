
/*
    domlistContainer.js, Dominion, the WebAbility(r) Database Abstraction Layer
    Contains the javascript class to manage a Dominion List Container in WAJAF
    (c) 2008-2010 Philippe Thomassigny

    This file is part of Dominion

    Dominion is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Dominion is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Dominion.  If not, see <http://www.gnu.org/licenses/>.
*/

function domlistContainer(domNodeFather, domID, params, notify, _4glNode)
{
  var self = this;
  this.type = 'container';
  this._4glNode = _4glNode;
  this.domNodeFather = domNodeFather;
  this.domID = domID;
  this.params = params;
  this.notify = notify;
  this.running = false;
  this.visible = true;

  this.mainzone = null;     // hierarchy entry
  this.zones = {};          // index for fast access
  this.templates = {};      // all the knows templates for this tree
  this.data = {};           // all the data rows we can use for this tree

  this.domNode = WA.createDomNode('ul', domID, null);
  domNodeFather.appendChild(this.domNode);

  this.classname = params.attributes.classname!=undefined?params.attributes.classname:'tree';
  this.classnamezone = params.attributes.classnamezone!=undefined?params.attributes.classnamezone:'treezone';

  this.domNode.className = this.classname;

  this.callNotify = callNotify;
  function callNotify(type, id)
  {
    var result = true;
    // no notifications if the app is not started
    if (self.notify && self.running)
      result = self.notify(type, self.domID, (id!=null?{id:id}:null));
    return result;
  }

  this.createZone = createZone;
  function createZone(domID, params, notify)
  {
    // 1. call event predestroy
    if (!self.callNotify('precreate', null))
      return null;

    if (!params.attributes.id)
      throw 'Error: the id is missing in the tree construction of '+domID;

    var container = self.domNode;
    if (params.attributes.father != undefined)
    {
      params.level = self.zones[params.attributes.father].level + 1;
      container = self.zones[params.attributes.father].domNodeChildren;
    }

    var z = new treeZone(this, domID, container, params, notify);

    self.zones[params.attributes.id] = z;

    if (self.running)
    {
      z.start();
    }

    self.callNotify('postcreate', params.attributes.id);

    return z;
  }

  this.destroyZone = destroyZone;
  function destroyZone(id)
  {
/*
    var i = WA.getIndexById(self.zones, id, 'domID');
    if (i === false)
      return;

    // 1. call event predestroy
    if (!self.callNotify('predestroy', i))
      return;

    self.zones[i].destroy();
    self.zones.splice(i,1);
    if (self.activezone == i)
    {
      // next available zone must be activated
      if (self.zones[i] != undefined)
        self.activateZone(i);
      else if (i > 0) // or previous if it was last one
        self.activateZone(i-1);
      else // or nothing activated if no zones
        self.activezone = -1;
    }
    self.callNotify('postdestroy', null);
*/
  }

  this.show = show;
  function show()
  {
    if (!self.callNotify('preshow', self.domID))
      return;
    self.domNode.style.display = '';
    self.visible = true;
    self.resize();
    self.callNotify('postshow', self.domID);
    // finaly ask for a general resize
    self.callNotify('resize', null);
  }

  this.hide = hide;
  function hide()
  {
    if (!self.callNotify('prehide', self.domID))
      return;
    self.visible = false;
    self.domNode.style.display = 'none';
    self.callNotify('posthide', self.domID);
  }

  this.setSize = setSize;
  function setSize(w,h)
  {
    if (w !== null)
      self.domNode.style.width = w + 'px';
    if (h !== null)
      self.domNode.style.height = h + 'px';
    self.resize();
    // finaly ask for a general resize
    self.callNotify('resize', null);
  }

  this.setPosition = setPosition;
  function setPosition(l,t)
  {
    if (l !== null)
      self.domNode.style.left = l + 'px';
    if (t !== null)
      self.domNode.style.top = t + 'px';
  }

  // getvalues, setvalues, start, stop, resize and destroy are controlled by 4GL so no notifications are needed
  this.getValues = getValues;
  function getValues()
  {
    return null;
  }

  this.setValues = setValues;
  function setValues(values)
  {
  }

  this.start = start;
  function start()
  {
    // we start all children
    for (var i in self.zones)
      self.zones[i].start();
    this.running = true;
    self.resize();

    // do we populate data from here ?
    if (self.data.row)
    {
      for (var i in self.data.row)
      {
        var myt = WA.clone(self.templates[self.data.row[i].template]);
        WA.replaceTemplate(myt, self.data.row[i]);
        myt.tag = 'zone';
        if (!myt.attributes)
          myt.attributes = {};
        myt.attributes.id = self.data.row[i].id;
        myt.attributes.father = self.data.row[i].father;
        myt.attributes.closeable = self.data.row[i].closeable?'yes':'no';
        myt.attributes.closed = self.data.row[i].closed?'yes':'no';
        myt.attributes.loadable = self.data.row[i].loadable?'yes':'no';
        myt.attributes.loaded = self.data.row[i].loaded?'yes':'no';
        self._4glNode.newTree(self._4glNode, myt);
      }
    }

  }

  this.resize = resize;
  function resize()
  {
    if (!self.running || !self.visible)
      return;
    // 1. resize main container
    self._4glNode.nodeResize(self.domNodeFather, self.domNode, self.params.attributes);
    // 2. resize active zone
//    if (self.activezone != -1)
//      self.zones[self.activezone].resize();
  }

  this.stop = stop;
  function stop()
  {
    this.running = false;
//    for (var i = 0, l = self.zones.length; i < l; i++)
//      self.zones[i].stop();
  }

  this.destroy = destroy;
  function destroy()
  {
    if (self.running)
      self.stop();
    // destroy all zones
    self.domNode = null;
    self.zones = null;
    self.mainzone = null;
    self.notify = null;
    self.params = null;
    self.domID = null;
    self.domNodeFather = null;
    self._4glNode = null;
    self = null;
  }

  // get the templates if any
  this.parseTemplates = parseTemplates;
  function parseTemplates(params)
  {
    for (var i in params)
    {
      if (params[i].tag == 'template')
      {
        self.templates[params[i].attributes.name] = params[i];
      }
    }
  }

  this.parseData = parseData;
  function parseData(params)
  {
    for (var i in params)
    {
      if (params[i].tag == 'dataset')
      {
        self.data = WA.JSON.decode(params[i].data);
      }
    }

  }

  this.parseTemplates(params);
  this.parseData(params);
}

// Needed aliases
WA.Containers.dblistContainer = dblistContainer;

