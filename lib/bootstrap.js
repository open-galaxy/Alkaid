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
  const compiledWrapper = vm.compileFunction(content, filename, params, []);
  compiledWrapper.call(thisValue, exports, require, module);

  moduleCache[filename] = module;
  return module.exports;
}

function loadModuleByBuiltin(filenames) {
  for (let index = 0; index < filenames.length; index++) {
    const filename = filenames[index];
    
    const module = require(filename);
    Object.defineProperty(globalThis, filename, {
      enumerable: true,
      configurable: false,
      writable: false,
      value: module,
    });
  }
}

loadModuleByBuiltin([
  'addEventListener',
  'fetch',
  'console',
]);

const entryScriptName = process.argv[1];
vm.runScript(fs.readFile(entryScriptName), entryScriptName);

})();
