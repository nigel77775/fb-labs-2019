let mas = [1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0];
let mas1 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1];

let shift=[];
let i = 0;

while(mas!=mas1){
  i++;
  let test = mas[i] * mas1[i];
   if(test = 0){
      mas1.shift();
      mas1.push(0);
      shift.push(mas1.shift());
   }
   else if (test != 0){
     mas1.shift();
     mas1.push(1);
     shift.push(mas1.shift());
   }
}
