window.onload = function(){
	var w = [
		[0.2, 0.4, -0.5],
		[-0.3, 0.1, 0.2],
		[-0.3, -0.2]
	], // 初始权值
		O =[1,0,1], // 输入{1,0,1}
		q =[-0.4, 0.2, 0.1], // 偏置
		l = 0.9; // 学习率

	network (w,O,q,l,1);

}


sigmoid函数计算 有效值取小数点后三位
function sigmoid(exponent) {

	var output = 1 / (1 + (Math.E ** -exponent));

	output = ( Math.round(output * 1000)) / 1000;

	return output;
}

// S_j = ∑_j(w_ij * O_j) + ø_j

function allSum_input(w,O,q) {

	var Oj =[0,0,0],
		i,
		j,
		len;

	for(i = 0,len = w.length;i < len ;i++){

		for(j = 0;j < len;j++){

			if(i !== len - 1){
				Oj[i] += w[i][j] * O[j];
				// 当j=2，即最后一次运算+偏置q[i]
				while(j === len - 1){
					Oj[i] += q[i];
					Oj[i] = sigmoid(Oj[i]);
					break;
				}
			} else {
				Oj[i] += Oj[j] * w[i][j];

				if(j === len -2){
					Oj[i] +=q[i];
					Oj[i] = sigmoid(Oj[i]);
					break;
				}
			}
		}

	}

	return Oj;
}

// 每个神经单元的误差算
function Eerr (Oj,w) {

	var Ej =[0,0,0],
		i,
		j,
		len;

	for(len = Oj.length,i = len -1;i >= 0;i--){


		if(i === len - 1){
			Ej[i] = Oj[i] * (1 - Oj[i]) * (1 - Oj[i]);
			Ej[i] = Math.round((Ej[i]*10000))/10000;
		} else {
			Ej[i] = Oj[i] * (1 - Oj[i]) * Ej[len-1] * w[2][i];
			Ej[i] = Math.round((Ej[i]*10000))/10000;
		}
	}

	return Ej;
}

// 权值调整和偏置调整
function weight (w,q,Ej,O,Oj,l){

	var i,
		j,
		len;

	for(i = 0,len = q.length;i < len;i++){
		q[i] = q[i] + l * Ej[i];
		q[i] = ( Math.round(q[i] * 1000)) / 1000;
	}
	// console.log(q);
	for(i = 0;i < len; i++){

		for(j = 0;j < len;j++){
// debugger
			if(i <= 1){

				w[i][j] = w[i][j] + l * Ej[i] * O[j];
				w[i][j] = ( Math.round(w[i][j] * 1000)) / 1000;
			} else {
				w[i][j] = w[i][j] + l * Ej[i] *Oj[j];
				w[i][j] = (Math.round(w[i][j] * 1000)) / 1000;
				if(j===1){break;}
			}
		}
	}

}


// 总体计算

function network (w,O,q,l,num) {

	var Oj = [],
		Ej = [],
		i;



	for( i =0;i < num;i++){

		Oj = allSum_input(w,O,q); // 计算输出Oj
		Ej = Eerr(Oj,w); // 计算各神经元误差Ej

		weight(w,q,Ej,O,Oj,l); // 重置w和q

	}
	console.log(w);
	console.log(q);

}

window.onload = function(){
	var w = [
		[0,2],
		[2,1],
		[1, 1]
	], // 初始权值
		O =[1,0], // 输入{1,0}
		q =[0, 0, 0], // 偏置
		l = 1; // 学习率

	network (w,O,q,l,1);

}
// 函数计算 有效值取小数点后三位
function sigmoid(exponent) {

	if(exponent >= 1){

		return exponent;
	} else {
		return 1;
	}
}

// 导数

function Odao (Oj) {
	if(Oj >= 1) {
		return 1;
	} else {
		return 0;
	}
}

// // S_j = ∑_j(w_ij * O_j) + ø_j

function allSum_input(w,O,q) {

	var Sj =[0,0,0],
		i,
		j,
		len;
// debugger
	for(i = 0,len = w.length;i < len ;i++){

		for(j = 0;j < len -1 ;j++){

			if(i !== len - 1){
				Sj[i] += w[i][j] * O[j];
				// 当j=2，即最后一次运算+偏置q[i]
				while(j === len - 2){
					Sj[i] += q[i];
					// Oj[i] = sigmoid(Oj[i]);
					break;
				}
			} else {
				Sj[i] += sigmoid(Sj[j]) * w[i][j];

				if(j === len -2){
					Sj[i] += q[i];
					// Oj[i] = sigmoid(Oj[i]);
					break;
				}
			}
		}

	}
	console.log("Sj:");
	console.log(Sj);
	return Sj; // sj
}

// // 每个神经单元的误差算
function Eerr (Sj,w) {

	var Ej =[0,0,0],
		i,
		j,
		len;

	for(len = Sj.length,i = len -1;i >= 0;i--){


		if(i === len - 1){
			Ej[i] =  Odao(Sj[i]) * (1 - sigmoid(Sj[i]));
			Ej[i] = Math.round((Ej[i]*10000))/10000;
		} else {
			Ej[i] =  Odao(Sj[i]) * Ej[len-1] * w[2][i];
			Ej[i] = Math.round((Ej[i]*10000))/10000;
		}
	}
console.log("EJ:");
console.log(Ej);
	return Ej;
}



// // 权值调整和偏置调整
function weight (w,q,Ej,O,Sj,l){

	var i,
		j,
		len;

	for(i = 0,len = q.length;i < len;i++){
		q[i] = q[i] + l * Ej[i];
		q[i] = ( Math.round(q[i] * 1000)) / 1000;
	}
	// console.log(q);
	for(i = 0;i < len; i++){

		for(j = 0;j < len;j++){
// debugger
			if(i <= 1){

				w[i][j] = w[i][j] + l * Ej[i] * O[j];
				w[i][j] = ( Math.round(w[i][j] * 1000)) / 1000;
				if(j===len-2){break;}
			} else {
				w[i][j] = w[i][j] + l * Ej[i] * sigmoid(Sj[j]);
				w[i][j] = (Math.round(w[i][j] * 1000)) / 1000;
				if(j===1){break;}
			}
		}
	}

}


// // 总体计算

function network (w,O,q,l,num) {

	var Oj = [],
		Ej = [],
		i;



	for( i =0;i < num;i++){

		Sj = allSum_input(w,O,q); // 计算输出Oj
		Ej = Eerr(Oj,w); // 计算各神经元误差Ej

		weight(w,q,Ej,O,Sj,l); // 重置w和q

	}
	console.log(w);
	console.log(q);

}


// sigmoid函数计算 有效值取小数点后三位
function sigmoid(exponent) {

	var output = 1 / (1 + (Math.E ** -exponent));

	output = ( Math.round(output * 1000)) / 1000;

	if(output > 0.5){

		return 1;
	} else {
		return -1;
	}

}


