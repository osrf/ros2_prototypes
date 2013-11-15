from __future__ import print_function


class _ROSMetaclass(type):

    # The ROS metaclass is completely independent from the storage backend
    # and the message structure, therefore we can reuse it with any
    # message
    def __new__(meta, name, bases, dct):
        class_inst = super(_ROSMetaclass, meta).__new__(meta, name, bases,
            dct)

        for attr, typ in class_inst.SCHEMA:
            getter = _ROSMetaclass._generate_ros_getter(attr)
            setter = _ROSMetaclass._generate_ros_setter(attr, typ)

            prop = property(getter, setter)
            setattr(class_inst, attr, prop)
        return class_inst

    def __call__(self, *args, **kwargs):
        obj = type.__call__(self, *args)
        obj._storage = obj.__ros_storage__()
        return obj

    @classmethod
    def _generate_ros_getter(meta, attr):
        def getter(obj):
            return getattr(obj._storage, attr)
        return getter

    @classmethod
    def _generate_ros_setter(meta, attr, typ):
        def setter(obj, value):
            # We have to do strict type-checking before serialization
            if typ is type(value):
                setattr(obj._storage, attr, value)
            else:
                raise TypeError("Wrong type for attribute: %s: %r vs %r" % (
                    attr, type(value), typ))
        return setter


class _FooPlainStorage(object):

    # bar and baz can be members as well, we are just using properties to be
    # to inject code

    def getbar(self):
        return self._bar

    def setbar(self, value):
        self._bar = value

    bar = property(getbar, setbar)

    def getbaz(self):
        return self._baz

    def setbaz(self, value):
        self._baz = value

    baz = property(getbaz, setbaz)


class Foo(object):
    __metaclass__ = _ROSMetaclass
    __ros_storage__ = _FooPlainStorage

    # Schema is in the class to decouple the message representation from the
    # storage backend
    SCHEMA = (('bar', bool), ('baz', int))


if __name__ == '__main__':
    f = Foo()
    f.bar = True
    assert(f.bar == True)

    f.baz = 42
    assert(f.baz == 42)

    try:
        # baz is declared as int, can't take a string
        f.baz = "hello"
    except TypeError as e:
        pass

    assert(f.baz == 42)
