
// https://kripken.github.io/emscripten-site/docs/porting/connecting_cpp_and_javascript/Interacting-with-code.html

var Poki = {

        // This can be accessed from the bootstrap code in the .html file
        $POKI: {
            _data: '',
            _cstr: null,

            GetTestData : function() {
                if (typeof window !== 'undefined') {
                    return POKI._data;
                }
                else {
                    return '';
                }
            },

            SetTestData : function(data) {
                if (typeof window !== 'undefined') {
                    POKI._data = data;
                }
            },
        },

        // These can be called from within the extension, in C++
        testGetUserData: function() {
            if (null == POKI._cstr) {
                var str = POKI.GetTestData();                 // get the data from java script
                if (str != '') {
                    POKI._cstr = _malloc(str.length + 1);         // allocate C++ memory to store it in
                    Module.writeStringToMemory(str, POKI._cstr, false);  // copy the data into the C array
                }
            }
            return POKI._cstr;
        },

        testClearUserData: function() {
            POKI._data = ''
            POKI._cstr = null
        }
}

autoAddDeps(Poki, '$POKI');
mergeInto(LibraryManager.library, Poki);
