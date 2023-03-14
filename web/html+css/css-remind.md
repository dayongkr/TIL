# CSS Remind

## 기본 개념

### 용어

``` css
a {
  color: red;
}
```

- a: selector
- {} 안에 내용: Declaration
- color: property
- red: value

### Specificity

브라우저의 알고리즘을 사용해 CSS declaration을 결정하는 것으로 CSS selector의 weight를 계산해 결정하게 된다. Weight은 ID-CLASS-TYPE와 같이 3열로 측정하게 된다.

#### Select weight

- ID
  - ID selectors
- CLASS
  - class selectors, attribute selectors, pseudo-classes(:hover)
- TYPE
  - type selectors, pseudo-elements(::before)
- No value
  - *, :where()는 weight에 영향을 주지 않는다.
  - :not(), :is(), :has()도 영향을 주지 않는다.

``` css
:root #myApp input:required {/* 1-2-1 */
  ...
}   
```

\#myApp으로 ID +1, :root, :required로 CLASS +1 * 2, input으로 TYPE +1 해서 1-2-1 weight를 최종적으로 가지게 된다.

#### Comparison

``` css
#myElement {
  color: green; /* 1-0-0  - WINS!! */
}
.bodyClass .sectionClass .parentClass [id="myElement"] {
  color: yellow; /* 0-4-0 */
}
```

ID가 더 높은 declaration 만약에 같으면 CLASS 가 더 높은 declaration 이렇게 내려가면서 비교하게 된다. 만약에 3열이 모두 같으면 마지막에 선언된 것이 이기게 된다.

다만 inline으로 style을 입히면 inline에 최우선이게 된다. 다만 value 옆에 !important를 적게되면 inline도 override 할 수 있다. 다만 너무 남용하지 말자.

> ref. [Specificity - MDN](https://developer.mozilla.org/en-US/docs/Web/CSS/Specificity)