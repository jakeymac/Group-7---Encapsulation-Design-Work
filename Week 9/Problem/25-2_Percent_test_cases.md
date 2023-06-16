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



assert (computePay(0,0.00) == 0.00);
assert (computePay(0, 8.00) == 0.00);
assert (computePay(1, 8.00) == 8.00);
assert (computePay(1,0.00) == 0.00);
assert (computePay(39, 10.00) == 390.00);
assert (comptuePay(40,10.00) == 400.00);
assert (computePay(41, 10.00) == 415.00);
assert (computePay(80,10.00) == 1000.00);
assert (computePay(-1,10.00) == null);
assert(computePay(1,-8.00) == null);
assert (computePay(168, 10.00) == null);

//Set 50%
void TestPercent::???()
{
   // setup
    Percent myPercent = Percent();
   // exercise
    myPercent.set(50.0);
   // verify
    assert(myPercent.percent == 0.5);
   // teardown
    delete(myPercent);
}


Class TestCoordinate: public TestCase {
Public:
    Void run() 
    {
        test_get_row_zero();
        test_get_row_one();
        test_get_row_twp();
        test_get_row_three();
        test_get_row_four();
        test_get_row_five();
        test_get_row_six();
        test_get_row_seven();


        test_get_column_zero();
        test_get_column_one();
        test_get_column_twp();
        test_get_column_three();
        test_get_column_four();
        test_get_column_five();
        test_get_column_six();
        test_get_column_seven();
        
        test_set_valid_coordinates();
        test_set_invalid_row();
        test_set_invalid_col();
        test_set_negative_coordiantes();
        test_set_too_large_coordinates();
        test_dispaly();
        

    }
private:
    void test_get_row_zero();    
    void test_get_row_one();
    void test_get_row_twp();
    void test_get_row_three();
    void test_get_row_four();
    void test_get_row_five();
    void test_get_row_six();
    void test_get_row_seven();

    void test_get_column_zero();
    void test_get_column_one();
    void test_get_column_twp();
    void test_get_column_three();
    void test_get_column_four();
    void test_get_column_five();
    void test_get_column_six();
    void test_get_column_seven();

    void test_set_valid_coordinates();
    void test_set_invalid_row();
    void test_set_invalid_col();
    void test_set_negative_coordiantes();
    void test_set_too_large_coordinates();

    void test_dispaly();
}
