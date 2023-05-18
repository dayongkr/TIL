# Promise & Async/Await

> ref. [Promises, async/await](https://javascript.info/callbacks)

## Callback function

자바스크립트에는 비동기로 처리하는 함수가 많다. 따라서 해당 함수 처리가 끝나면 어떤 작업을 수행하고 싶을 때에는 단순히 아래에 코드를 작성하면 원하는 결과를 얻을 수 없다. 이때 사용하는 것이 콜백 함수이다.

```js
function loadScript(src, callback) {
  let script = document.createElement("script");
  script.src = src;

  script.onload = () => callback(script); // script가 로드되면 callback 함수를 호출한다.

  document.head.append(script);
}
```

하지만 이러한 callback function 안에 또 다른 callback function을 넣어야 하는 경우가 생긴다. 이러한 경우를 콜백 지옥이라고 한다. 최종적으로 이를 해결하려면 Promise를 사용해야 한다.

## Promise

promise는 결과를 기다리다가 소비를 하는 주체와 결과를 만들어내는 주체를 분리시킨다. 이를 관리하는 것이 Promise이다.

```js
let promise = new Promise(function (resolve, reject) {
  // executor (the producing code, "singer")
});
```

resolve와 reject는 js에서 자체 제공하는 콜백 함수로 resolve는 성공했을 때 결과를 value로 전달하고, reject는 실패했을 때 결과를 error로 전달한다.

Promise 객체에는 state, result 두 가지 프로퍼티가 있다. state는 pending, fulfilled, rejected 세 가지 상태를 가지며, result는 pending일 땐 undefined, fulfilled일 땐 value, rejected일 땐 error를 가진다.

> state와 result는 외부에서 접근할 수 없다.

```js
let promise = new Promise(function (resolve, reject) {
  // pending 상태
  // 1초 후에 result가 1이 되는 작업을 수행한다.
  setTimeout(() => resolve(1), 1000);
});
```

위와 같이 Promise 객체를 생성하면 executor 함수가 바로 실행된다. resolve 함수가 실행되면 state는 fulfilled가 되고, result는 1이 된다.

```js
let promise = new Promise(function (resolve, reject) {
  // pending 상태
  // 1초 후에 result가 1이 되는 작업을 수행한다.
  setTimeout(() => reject(new Error("에러 발생!")), 1000);
});
```

reject 함수가 실행되면 state는 rejected가 되고, result는 Error 객체가 된다. 둘 중에 하나가 실행되면 더 이상 다른 것은 실행되지 않는다.

### Consumer: then, catch, finally

Promise 객체를 생성하면 executor 함수가 바로 실행되고, 이후에는 then, catch, finally 메서드를 통해 Promise 객체를 소비할 수 있다.

```js
promise.then(
  function (result) {
    /* handle a successful result */
  },
  function (error) {
    /* handle an error */
  }
);
```

then 메서드는 두 개의 콜백 함수를 인자로 받는다. 첫 번째 콜백 함수는 resolve가 실행되었을 때, 두 번째 콜백 함수는 reject가 실행되었을 때 실행된다.

```js
promise.catch(function (error) {
  /* handle error */
});
```

catch 메서드는 reject가 실행되었을 때 실행된다.

```js
promise.finally(function () {
  /* do something */
});
```

finally 메서드는 Promise 객체가 settled 상태가 되었을 때 실행된다. finally 메서드는 인자로 콜백 함수를 받지 않는다. 따라서 then, catch 메소드를 뒤에 사용해야 한다.

### Promise chaining

then, catch 메서드는 Promise 객체를 반환한다. 따라서 then, catch 메서드를 여러 번 사용할 수 있다. 이를 Promise chaining이라고 한다.

```js
new Promise(function (resolve, reject) {
  setTimeout(() => resolve(1), 1000);
})
  .then(function (result) {
    alert(result); // 1
    return result * 2;
  })
  .then(function (result) {
    alert(result); // 2
    return result * 2;
  })
  .then(function (result) {
    alert(result); // 4
    return result * 2;
  });
```

then 메서드는 콜백 함수의 반환값을 다음 then 메서드의 콜백 함수의 인자로 전달한다.

#### then vs catch

```js
// then + catch
promise.then(f1).catch(f2);
// only then
promise.then(f1, f2);
```

둘은 다른 동작을 한다. 첫 번째는 f1이 실행되었을 때 에러가 발생하면 f2가 실행되지만, 두 번째는 f1이 실행되었을 때 에러가 발생하면 f2가 실행되지 않는다.

### 에러 핸들러

catch를 사용하여 에러를 핸들링할 수 있다. 추가로 Promise 안에서 발생한 에러는 암시적으로 reject처럼 처리되기 때문에 어떠한 에러가 발생하더라도 catch로 잡을 수 있다.

또한 매번 catch를 추가할 필요는 없고 마지막에 한 번만 추가해도 위의 모든 then 메서드에서 발생한 에러를 잡을 수 있다. 단 그 사이에 있는 then 메서드는 실행되지 않는다.

> 다만 모든 경우에 catch를 추가할 필요는 없고 만약에 에러를 잡고 싶으면 unhandledrejection 이벤트 핸들러를 추가하면 된다.

### Promise API

여러 Promise 객체가 있을 때, 모든 Promise 객체가 fulfilled 상태가 되면 then 메서드가 실행되고, 하나라도 rejected 상태가 되면 catch 메서드가 실행되게 하고 싶을 때가 있다. 이럴 때 사용하는 메서드가 Promise.all이다.

```js
Promise.all([promise1, promise2, ...]);
```

반환되는 값은 배열로 모든 Promise 객체의 result를 담고 있다. 이때 순서는 Promise.all에 전달한 배열의 순서와 같다.

만약에 성공된 Promise 따로 실패한 Promise 따로 처리하고 싶다면 Promise.allSettled를 사용하면 된다.

추가로 프라미스 중 가장 먼저 fulfilled 된 프라미스만 처리하고 싶다면 Promise.race를 사용하면 된다.

## Async/Await

async와 await를 사용하면 promise를 더 쉽게 사용할 수 있다.

### Async function

```js
async function f() {
  return 1;
}
```

async function은 항상 promise를 반환한다. 위 함수는 result가 1인 promise를 반환한다. 명시적으로도 promise를 반환할 수 있다.

```js
async function f() {
  return Promise.resolve(1);
}
```

### Await

await는 async 함수 안에서만 사용할 수 있다. await는 promise가 settled 상태가 될 때까지 기다린다. promise가 fulfilled 상태가 되면 result를 반환하고, rejected 상태가 되면 error를 발생시킨다.

```js
async function f() {
  let promise = new Promise((resolve, reject) => {
    setTimeout(() => resolve("완료!"), 1000);
  });

  let result = await promise; // promise가 settled 상태가 될 때까지 기다린다.

  alert(result); // "완료!"
}
```

reject가 발생하면 try...catch 문을 사용해 에러를 처리할 수 있다.

```js
async function f() {
  try {
    let response = await fetch("http://no-such-url");
  } catch (err) {
    alert(err); // TypeError: failed to fetch
  }
}
```

async와 await을 사용하면 기존의 try catch문을 사용할 수 있고 코드가 더 직관적이다.
