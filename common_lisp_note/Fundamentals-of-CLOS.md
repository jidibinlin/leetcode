- [Classes and instances](#org610cdcf)
- [Defining classes (defclass)](#org4364a5d)
- [创建对象(make-instance)](#orgdec7463)
- [Slots](#org00e4a8d)
  - [A function that always works(slot-value)](#org5d8f406)
  - [初始化和默认值(initarg,initform)](#orgd4a046a)
  - [Getters and Setters (accessor,reader,writer)](#org0b2282d)
  - [Class VS instance slots](#org9ff0c40)
  - [Slot documentation](#org9040564)
  - [Slot type](#orgc6e7689)
- [find-class,class-name,class-of](#orgb42d9de)
- [Subclasses 和 inheritance](#org764a755)
- [Multiple inheritance](#org3af4c82)
- [Redefining and changing a class](#orgd1cda0d)
- [Pretty printing](#org2fc1897)
- [Classes of traditional lisp types](#org0ba6ca9)
- [Introspection](#org34bb57a)
- [See also](#orgaa3a0bb)
  - [defclass/std: write shorter classes](#org965e0d6)
- [Methods](#orgc3c0e90)
  - [先来个潜入](#org2b1db6d)
  - [Generic functions (defgeneric,defmethod)](#orgcd499dd)

<!--more-->

CLOS is the “Common Lisp Object System”, arguably one of the most powerful object systems available in any language. Some of its features include:

-   it is dynamic, making it a joy to work with in a Lisp REPL. For example, changing a class definition will update the existing objects, given certain rules which we have control upon.
-   it supports multiple dispatch and multiple inheritance,
-   it is different from most object systems in that class and method definitions are not tied together,
-   it has excellent introspection capabilities,
-   it is provided by a meta-object protocol, which provides a standard interface to the CLOS, and can be used to create new object systems.
-   The functionality belonging to this name was added to the Common Lisp language between the publication of Steele’s first edition of “Common Lisp, the Language” in 1984 and the formalization of the language as an ANSI standard ten years later.

This page aims to give a good understanding of how to use CLOS, but only a brief introduction to the MOP.

To learn the subjects in depth, you will need two books:

-   [Object-Oriented Programming in Common Lisp: a Programmer\`s Guide to CLOS](http://www.communitypicks.com/r/lisp/s/17592186046723-object-oriented-programming-in-common-lisp-a-programmer)
-   [the Art of the Metaobject Protocol](http://www.communitypicks.com/r/lisp/s/17592186045709-the-art-of-the-metaobject-protocol)


<a id="org610cdcf"></a>

# Classes and instances

先来个简单的例子 包含class的定义，对象的创建，slot的访问，methods的指定，以及继承

```lisp
(defclass person ()
  ((name
    :initarg :name
    :accessor name)
   (lisper
    :initform nil
    :accessor lisper)))

;; => #<STANDARD-CLASS PERSON>

(defvar p1 (make-instance 'person :name "me" ))
;;                                 ^^^^ initarg
;; => #<PERSON {1006234593}>

(name p1)
;;^^^ accessor
;; => "me"

(lisper p1)
;; => nil
;;    ^^ initform (slot unbound by default)

(setf (lisper p1) t)


(defclass child (person)
  ())

(defclass child (person)
  ((can-walk-p
     :accessor can-walk-p
     :initform t)))
;; #<STANDARD-CLASS CHILD>

(can-walk-p (make-instance 'child))
;; T
```


<a id="org4364a5d"></a>

# Defining classes (defclass)

CLOS中定义一个新的数据类型使用defclass macro

```lisp
(defclass person ()
  ((name
    :initarg :name
    :accessor name)
   (lisper
    :initform nil
    :accessor lisper)))
```

这样我们就得到了一个CLOS 类型（class）叫做person,person 有两个slot 一个叫做name 一个叫做lisper。

```lisp
(class-of p1)
#<STANDARD-CLASS PERSON>

(type-of p1)
PERSON
```

defclass 的通用形式

```lisp
(defclass <class-name> (list of super classes)
  ((slot-1
    :slot-option slot-argument)
   (slot-2,etc))
  (:optional-class-option
   :another-optional-class-option))
```

所以person class 并没有显式的继承任何class. 但是他默认继承了standard-object.

我们也可以写一个非常小的class 不用slot options

```lisp
(defclass point ()
  (x y z))
```

甚至都不需要slot (defclass point()())


<a id="orgdec7463"></a>

# 创建对象(make-instance)

```lisp
(defvar p1 (make-instance 'person :name "me"))
```

更实用的方法是定义构造函数

```lisp
(defun make-person (name &key lisper)
  (make-instance 'person :name name :lisper lisper))
```


<a id="org00e4a8d"></a>

# Slots


<a id="org5d8f406"></a>

## A function that always works(slot-value)

在任何时候都可以用来用来访问slot的函数时 (slot-value <object> <slot-name>)

```lisp
(defvar pt (make-instance 'point))

(inspect pt)
The object is a STANDARD-OBJECT of type POINT.
0. X: "unbound"
1. Y: "unbound"
2. Z: "unbound"
```

这样你可以获得一个point对象，但是他的slots 默认是没有绑定的，尝试访问他们会导致UNBOUND-SLOT condition

```lisp
(slot-value pt 'x) ;; => condition: the slot is unbound
```

slot-value 是可以被setf 的

```lisp
(setf (slot-value pt 'x) 1)

(slot-value pt 'x) ;; => 1
```


<a id="orgd4a046a"></a>

## 初始化和默认值(initarg,initform)

-   :initarg :foo 是用来传给make-instance 让make-instance 给slot 设置值的关键字
    
    ```lisp
    (make-instance 'person :name "me")
    ```

-   :initform <val> 是当我们没有显式指定initarg时，设置的默认值。在defclass的词法作用域中
    
    ```lisp
    (defclass foo ()
      ((a
        :initarg :a
        :initform (error "you didn`t supply an initial value for slot a"))))
    
    (make-instance 'foo) ;; => enters the debugger
    ```


<a id="org0b2282d"></a>

## Getters and Setters (accessor,reader,writer)

-   :accessor foo: accessor 既是getter 也是 setter.
    
    ```lisp
    (name p1) ;; => "me"
    
    (type-of #'name)
    STANDARD-GENERIC-FUNCTION
    ```
-   reader and writer 就是他们描述的功能，只有:writer是setf-able的

如果你不指定他们，你仍然可以使用slot-value 呢可以指定不止一个:accessor,:reader 或者 :initarg

这里介绍两个macros 让访问slot更加简洁

1.  with-slots 可以一次访问多个slot-value
    
    ```lisp
    (with-slots (name lisper) c1
      (format t "got ~a, ~a~&" name lisper))
    ```
    
    or
    
    ```lisp
    (with-slots ((n name)
                 (l lisper))
        c1
      (format t "got ~a, ~a~&" n l))
    ```
2.  with-accessor 也差不多，但是使用的accessor
    
    ```lisp
    (with-accessors ((name name)
                     (lisper lisper))
        p1
      (format t "name: ~a, lisper: ~a" name lisper))
    ```


<a id="org9ff0c40"></a>

## Class VS instance slots

:allocation 用来说明这个slot是local的还是shared

-   local slot 是默认的，也就是说，实例之间是不共享的 这时:allocation == :instance
-   shared slot 在实例间是共享的，我们可以用:allocation :class 来设置

在下面的例子中，注意 p2的species槽的值是如何变化的，以及是如何影响所有class的instance的

```lisp
(defclass person ()
  ((name :initarg :name :accessor name)
   (species
      :initform 'homo-sapiens
      :accessor species
      :allocation :class)))

;; Note that the slot "lisper" was removed in existing instances.
(inspect p1)
;; The object is a STANDARD-OBJECT of type PERSON.
;; 0. NAME: "me"
;; 1. SPECIES: HOMO-SAPIENS
;; > q

(defvar p2 (make-instance 'person))

(species p1)
(species p2)
;; HOMO-SAPIENS

(setf (species p2) 'homo-numericus)
;; HOMO-NUMERICUS

(species p1)
;; HOMO-NUMERICUS

(species (make-instance 'person))
;; HOMO-NUMERICUS

(let ((temp (make-instance 'person)))
    (setf (species temp) 'homo-lisper))
;; HOMO-LISPER
(species (make-instance 'person))
;; HOMO-LISPER
```


<a id="org9040564"></a>

## Slot documentation

任何slot 都可以接受一个:documentation option


<a id="orgc6e7689"></a>

## Slot type

:type 用来检查slot的类型，但是只有很少一部分的实现支持:type 类型检查


<a id="orgb42d9de"></a>

# find-class,class-name,class-of

```lisp
(find-class 'point)
;; #<STANDARD-CLASS POINT 275B78DC>

(class-name (find-class 'point))
;; POINT

(class-of my-point)
;; #<STANDARD-CLASS POINT 275B78DC>

(typep my-point (class-of my-point))
;; T
```


<a id="org764a755"></a>

# Subclasses 和 inheritance

child 是 person 的子类, 所有object 都继承自standard-object and t. 所有child instance 也是 person 的 instance

```lisp
(type-of cl)
;; child

(subtypep (type of cl) 'person)
;; T

(ql:quickload "closer-mop")
;; ...

(closer-mop:subclassp (class-of cl) 'person)
```

一个subclass 继承了他所有的 parents\` 的slots, 并且，他可以覆盖父类们的任何slot options.

child class的优先级是这样的

```lisp
child <- person <-- standard-object <- t
```

我们可以用closer-mop:class-precedence-list 去查看

```lisp
(closer-mop:class-precedence-list (class-of c1))
;; (#<standard-class child>
;;  #<standard-class person>
;;  #<standard-class standard-object>
;;  #<sb-pcl::slot-class sb-pcl::slot-object>
;;  #<sb-pcl:system-class t>)
```

但是child的直接父类只是

```lisp
(closer-mop:class-direct-superclasses (class-of c1))
;; (#<standard-class person>)
```

我们还可以用更多的方法来inspect classes,比如class-direct-[subclasses, slots, default-initargs]

slots 以如下方式结合

-   :accessor and :reader are combined by the union of accessors and readers from all the inherited slots.
-   :initarg: the union of initialization arguments from all the inherited slots.

-   :initform: we get the most specific default initial value form, i.e. the first :initform for that slot in the precedence list.

-   :allocation is not inherited. It is controlled solely by the class being defined and defaults to :instance.


<a id="org3af4c82"></a>

# Multiple inheritance

```lisp
(defclass baby (child person)
  ())
```

现代语言不提倡多重继承


<a id="orgd1cda0d"></a>

# Redefining and changing a class

这一节简短的包含两个话题

-   重定义已经存在的class
-   改变已经一个class 的instance

要重定义一个class,只需要在执行榆次defclass, 他会替换所有的旧的定义，包括实例，继承。

```lisp
(defclass person ()
  ((name
    :initarg :name
    :accessor name)
   (lisper
    :initform nil
    :accessor lisper)))

(setf pl (make-instance 'person :name "me"))
```

changing,adding,removing slots&#x2026;

```lisp
(lisper p1)
;; NIL

(defclass person ()
  ((name
    :initarg :name
    :accessor name)
   (lisper
    :initform t        ;; <-- from nil to t
    :accessor lisper)))

(lisper p1)
;; NIL (of course!)

(lisper (make-instance 'person :name "You"))
;; T

(defclass person ()
  ((name
    :initarg :name
    :accessor name)
   (lisper
    :initform nil
    :accessor lisper)
   (age               ;; <-- new slot
    :initarg :arg
    :initform 18      ;; <-- default value
    :accessor age)))

(age p1)
;; => 18. Correct. This is the default initform for this new slot.

(slot-value p1 'bwarf)
;; => "the slot bwarf is missing from the object #<person…>"

(setf (age p1) 30)
(age p1) ;; => 30

(defclass person ()
  ((name
    :initarg :name
    :accessor name)))

(slot-value p1 'lisper) ;; => slot lisper is missing.
(lisper p1) ;; => there is no applicable method for the generic function lisper when called with arguments #(lisper).
```

要改变一个实例的class, 可以使用change-class:

```lisp
(change-class p1 'child)

;; we can also set slots of the new class:
(change p1 'child :can-walk-p nil)

(class-of p1)
;; #<STANDARD-CLASS CHILD>

(can-walk-p p1)
;; T
```


<a id="org2fc1897"></a>

# Pretty printing

每次我们打印一个object 我们会获得一个这样的输出

```lisp
#<PERSON {1006234593}>
```

如果想要更多的信息，比如

```lisp
#<PERSON me lisper: t>
```

要想更加好看的打印可以指定 class 的 generic print-object 方法

```lisp
(defmethod print-object ((obj person) stream)
  (print-unreadable-object (obj stream :type t)
    (with-accessors ((name name)
                     (lisper lisper))
        obj
      (format stream "~a, lisper: ~a" name lisper))))
p1
;; #<PERSON me, lisper: T>
```

print-unreadable-object 打印#<&#x2026;>, 这表明 object 的reader无法再深入的读取. :type t 参数要求答应object-type的前缀，也就是 PERSON. 没有它我们会得到 #<me,lisper: T> 我们使用了with-accessors macro,但是对于简单的情况这样做就可以了的

```lisp
(defmethod print-object ((obj person) stream)
  (print-unreadable-object (obj stream :type t)
    (format stream "~a, lisper: ~a" (name obj) (lisper obj))))
```

<div class="admonition" id="org2cfc704">
<p>
尝试访问一个没有被绑定的slot会导致错误，所以应该先使用slot-boundp判断
</p>

</div>

下面的代码重现了默认的打印方式

```lisp
(defmethod print-object ((obj person) stream)
  (print-unreadable-object (obj stream :type t :identity t)))
```

这里:identity为t时将会打印地址


<a id="org0ba6ca9"></a>

# Classes of traditional lisp types

这节不是很明白贴出原文地址吧 [Classes of traditional lisp types](https://lispcookbook.github.io/cl-cookbook/clos.html#classes-of-traditional-lisp-types)


<a id="org34bb57a"></a>

# Introspection

其实Introspection就是各种判断CLOS instance内部结构的断言函数，如果你需要非常了解这些函数的话推荐去看看[closer-mop](https://github.com/pcostanza/closer-mop) 库和[CLOS & MOP specifications](https://clos-mop.hexstreamsoft.com/) 这里列出一些函数

```lisp
closer-mop:class-default-initargs
closer-mop:class-direct-default-initargs
closer-mop:class-direct-slots
closer-mop:class-direct-subclasses
closer-mop:class-direct-superclasses
closer-mop:class-precedence-list
closer-mop:class-slots
closer-mop:classp
closer-mop:extract-lambda-list
closer-mop:extract-specializer-names
closer-mop:generic-function-argument-precedence-order
closer-mop:generic-function-declarations
closer-mop:generic-function-lambda-list
closer-mop:generic-function-method-class
closer-mop:generic-function-method-combination
closer-mop:generic-function-methods
closer-mop:generic-function-name
closer-mop:method-combination
closer-mop:method-function
closer-mop:method-generic-function
closer-mop:method-lambda-list
closer-mop:method-specializers
closer-mop:slot-definition
closer-mop:slot-definition-allocation
closer-mop:slot-definition-initargs
closer-mop:slot-definition-initform
closer-mop:slot-definition-initfunction
closer-mop:slot-definition-location
closer-mop:slot-definition-name
closer-mop:slot-definition-readers
closer-mop:slot-definition-type
closer-mop:slot-definition-writers
closer-mop:specializer-direct-generic-functions
closer-mop:specializer-direct-methods
closer-mop:standard-accessor-method
```


<a id="orgaa3a0bb"></a>

# See also


<a id="org965e0d6"></a>

## defclass/std: write shorter classes

defclass/std 提供了一个简写defclass的macro 默认他会提供一个initarg 和一个绑定为nil的initform 给你的slot定义 比如

```lisp
(defclass/std example()
  ((slot1 slot2 slot3)))
```

会被展开为

```lisp
(defclass example()
  ((slot1
    :accessor slot1
    :initarg :slot1
    :initform nil)
   (slot2
    :accessor slot2
    :initarg :slot2
    :initform nil)

   (slot3
    :accessor slot3
    :initarg :slot3
    :initform nil)))
```

他很方便灵活，但是common lisp 社区很少使用他，你可以自行决定是否使用他


<a id="orgc3c0e90"></a>

# Methods


<a id="org2b1db6d"></a>

## 先来个潜入

之前有过person 和 child 类的定义

```lisp
(defclass person()
  ((name
    :initarg :name
    :accessor name)))
(defclass child (person)
  ())

(setf p1 (make-instance 'person :name "me"))
(setf p2 (make-instance 'child :name "Alice"))

```

```lisp
(defmethod greet (obj)
  (format t "Are you a person ? You are a ~a.~&" (type-of obj)))
;; style-warning: Implicitly creating new generic function common-lisp-user::greet.
;; #<STANDARD-METHOD GREET (t) {1008EE4603}>

(greet :anything)
;; Are you a person ? You are a KEYWORD.
;; NIL
(greet p1)
;; Are you a person ? You are a PERSON.

(defgeneric greet (obj)
  (:documentation "say hello"))
;; STYLE-WARNING: redefining COMMON-LISP-USER::GREET in DEFGENERIC
;; #<STANDARD-GENERIC-FUNCTION GREET (2)>

(defmethod greet ((obj person))
  (format t "Hello ~a !~&" (name obj)))
;; #<STANDARD-METHOD GREET (PERSON) {1007C26743}>

(greet p1) ;; => "Hello me !"
(greet c1) ;; => "Hello Alice !"

(defmethod greet ((obj child))
  (format t "ur so cute~&"))
;; #<STANDARD-METHOD GREET (CHILD) {1008F3C1C3}>

(greet p1) ;; => "Hello me !"
(greet c1) ;; => "ur so cute"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Method combination: before, after, around.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(defmethod greet :before ((obj person))
  (format t "-- before person~&"))
#<STANDARD-METHOD GREET :BEFORE (PERSON) {100C94A013}>

(greet p1)
;; -- before person
;; Hello me

(defmethod greet :before ((obj child))
  (format t "-- before child~&"))
;; #<STANDARD-METHOD GREET :BEFORE (CHILD) {100AD32A43}>
(greet c1)
;; -- before child
;; -- before person
;; ur so cute

(defmethod greet :after ((obj person))
  (format t "-- after person~&"))
;; #<STANDARD-METHOD GREET :AFTER (PERSON) {100CA2E1A3}>
(greet p1)
;; -- before person
;; Hello me
;; -- after person

(defmethod greet :after ((obj child))
  (format t "-- after child~&"))
;; #<STANDARD-METHOD GREET :AFTER (CHILD) {10075B71F3}>
(greet c1)
;; -- before child
;; -- before person
;; ur so cute
;; -- after person
;; -- after child

(defmethod greet :around ((obj child))
  (format t "Hello my dear~&"))
;; #<STANDARD-METHOD GREET :AROUND (CHILD) {10076658E3}>
(greet c1) ;; Hello my dear


;; call-next-method

(defmethod greet :around ((obj child))
  (format t "Hello my dear~&")
  (when (next-method-p)
    (call-next-method)))
;; #<standard-method greet :around (child) {100AF76863}>

(greet c1)
;; Hello my dear
;; -- before child
;; -- before person
;; ur so cute
;; -- after person
;; -- after child

;;;;;;;;;;;;;;;;;
;; Adding in &key
;;;;;;;;;;;;;;;;;

;; In order to add "&key" to our generic method, we need to remove its definition first.
(fmakunbound 'greet)  ;; with Slime: C-c C-u (slime-undefine-function)
(defmethod greet ((obj person) &key talkative)
  (format t "Hello ~a~&" (name obj))
  (when talkative
    (format t "blah")))

(defgeneric greet (obj &key &allow-other-keys)
  (:documentation "say hi"))

(defmethod greet (obj &key &allow-other-keys)
  (format t "Are you a person ? You are a ~a.~&" (type-of obj)))

(defmethod greet ((obj person) &key talkative &allow-other-keys)
  (format t "Hello ~a !~&" (name obj))
  (when talkative
    (format t "blah")))

(greet p1 :talkative t) ;; ok
(greet p1 :foo t) ;; still ok


;;;;;;;;;;;;;;;;;;;;;;;

(defgeneric greet (obj)
  (:documentation "say hello")
  (:method (obj)
    (format t "Are you a person ? You are a ~a~&." (type-of obj)))
  (:method ((obj person))
    (format t "Hello ~a !~&" (name obj)))
  (:method ((obj child))
    (format t "ur so cute~&")))

;;;;;;;;;;;;;;;;
;;; Specializers
;;;;;;;;;;;;;;;;

(defgeneric feed (obj meal-type)
  (:method (obj meal-type)
    (declare (ignorable meal-type))
    (format t "eating~&")))

(defmethod feed (obj (meal-type (eql :dessert)))
    (declare (ignorable meal-type))
    (format t "mmh, dessert !~&"))

(feed c1 :dessert)
;; mmh, dessert !

(defmethod feed ((obj child) (meal-type (eql :soup)))
    (declare (ignorable meal-type))
    (format t "bwark~&"))

(feed p1 :soup)
;; eating
(feed c1 :soup)
;; bwark
```


<a id="orgcd499dd"></a>

## Generic functions (defgeneric,defmethod)

在lisp方法中 generic function 是一个相关联的方法集合。所有同名的方法都属于同一个generic function defmethod 和 defun 很相似。他将函数名和函数体相关联，但是函数体只有当参数的类型和lambda list定义的类型相匹配时才会被执行。 他们可以有optional,keyword 和 &rest参数

<div class="admonition" id="org6881687">
<p>
lambda list 其实就是参数列表
</p>

</div>

defgeneric 用来定义generic function, 如果我们使用defmethod 的时候没有对应的defgeneric时，一个generic function就会被自动创建

使用defgenerics 是一个好习惯，我们可以添加默认的实现，甚至是documentation

```lisp
(defgeneric greet (obj)
  (:documentation "says hi")
  (:method (obj)
           (format t "Hi")))
```

一个方法的lambda list 所需要的参数可能有三种形式

1.  a simple variable:
    
    ```lisp
    (defmethod greet (foo)
      ...)
    ```
    
    这个method 可以接受任何的参数
2.  一个variable 和一个specializer
    
    ```lisp
    (defmethod greet ((foo person))
      ...)
    ```
    
    在这种情况下，foo 被绑定只有特定的class 比如person 和其 subclass才能使用这个方法

如果参数与specializer不匹配，那么就会报错 对于optional &key 参数我们不能使用specialize

1.  a variable 和一个eql specializer
    
    ```lisp
    
    ```
