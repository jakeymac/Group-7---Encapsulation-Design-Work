| Name | Setup | Exercise | Verify | 
| ---- | ----- | -------- | ------ |
| Get default     | Percent myPercent = Percent(); |  double returnValue = myPercent.get(); |  assert(returnValue == 0.0); <br> assert(myPercent.percent == 0.0); |
| Get 50% | Percent myPercent = Percent(); <br> myPercent.percent = 0.5; | double returnValue = myPercent.get(); | assert(returnValue == 50.0) <br> assert(myPercent.percent == 0.5); |
| Get 100% | Percent myPercent = Percent(); <br> myPercent.percent = 1.0; | double returnValue = myPercent.get(); | assert(returnValue == 100.0) <br> assert(myPercent.percent == 1.0); |
| Set 50%  | Percent myPercent = Percent(); | myPercent.set(50.0); | assert(myPercent.percent == 0.5); |
| Set 100%  | Percent myPercent = Percent(); | myPercent.set(100.0); | assert(myPercent.percent == 1.0); |
| Higher than 100%  | Percent myPercent = Percent(); | myPercent.set(101.0); | ensure error is thrown <br> assert(myPercent.percent == 0.0);|
| Lower than 0%  | Percent myPercent = Percent(); | myPercent.set(-1.0); | ensure error is thrown <br> assert(myPercent.percent == 0.0);|
|      |       |          |        |
|      |       |          |        |
|      |       |          |        |
|      |       |          |        |
|      |       |          |        |
