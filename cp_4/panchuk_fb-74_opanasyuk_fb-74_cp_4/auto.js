let result = document.getElementById('result').innerHTML.split('');
console.log(result);
const per = 41943;

function autocorrelation(result, per){
  let d = 0;
  while(d!=11){
     let sum = 0;
     let i = 0;
     while(i != per){
       sum += (result[i] + result[i+d] % per) % 2;
       i ++;
      }
  console.log('Autocorrelation ' + 'd: ' + d + 'sum: ' + sum);
}
  d ++;
}
