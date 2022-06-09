(function () {

const entryScriptName = process.argv[1];

vm.runScript(fs.readFile(entryScriptName), entryScriptName);

})();
