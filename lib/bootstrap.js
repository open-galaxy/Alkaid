(function () {

const moduleCache = Object.create(null);

function require(filename) {
  filename = `lib/${filename}.js`;
  const cachedModule = moduleCache[filename];
  if (cachedModule !== undefined) return cachedModule.exports;

  const params = ['exports', 'require', 'module'];
  const exports = {};
  const module = { exports };
  const thisValue = exports;

  const content = fs.readFile(filename);
  if (!content) return;

  const compiledWrapper = vm.compileFunction(content, filename, params, []);
  compiledWrapper.call(thisValue, exports, require, module);

  moduleCache[filename] = module;
  return module.exports;
}

function definePropertyByGlobal(property, value) {
  Object.defineProperty(globalThis, property, {
      enumerable: true,
      configurable: false,
      writable: false,
      value,
  });
}

const Event = require('./event');
const { fetch } = require('./fetch');

// load builtin module
definePropertyByGlobal('addEventListener', Event.addEventListener);
definePropertyByGlobal('fetch', fetch);

const entryScriptName = process.argv[1];
vm.runScript(fs.readFile(entryScriptName), entryScriptName);

})();
