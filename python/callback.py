class Foo(object):
  def __init__(self):
    self._bar_observers = []

  def add_bar_observer(self, observer):
    self._bar_observers.append(observer)

  def notify_bar(self, param):
    for observer in self._bar_observers:
      observer(param)

def observer(param):
  print "observer(%s)" % param

class Baz(object):
    v = 1
    def observer(self, param):
        print "Baz.observer(%s) v = %d" % (param, Baz.v)

class CallableClass(object):
  def __call__(self, param):
    print "CallableClass.__call__(%s)" % param

baz = Baz()

foo = Foo()

foo.add_bar_observer(observer) # function
foo.add_bar_observer(baz.observer) # bound method
foo.add_bar_observer(CallableClass()) # callable instance

foo.notify_bar(3)
