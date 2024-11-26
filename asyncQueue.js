/*
take a bunch of asynchronous tasks as input
these need to run in parallel but there's a limit to how many can run in parallel, defined by the maxParallelRequests input
take in a taskFunction as input that is executed by the exec function using the task
Basically at any give point of time, there should only be a maximum of maxParallelRequests number of execs running at a time(ie a maxParallelRequests no of requests made to the taskFunction)
Think of the taskFunction as say a call to some API service or something where too many requests to it can't be made at a time
*/

function taskFunction(task){
  //pay attention to this function
  //there's an inner promise from setTimeout which resolves after a timeout of task*1000ms
  //After resolution of setTimeout, the log is printed and resolve() is called, which resolves the outer promise sent by taskFunction to its caller
	return new Promise(resolve => setTimeout(() => {
	    if(task) console.log(`Finished task${task}`);//executes after setTimeout finishes waiting
	    resolve();//executes at the end to make sure the promise of taskFunction is resolved
	}, task*1000));//simulate working on task by waiting for 6s
}

function exec(taskFn, task){
	return taskFn(task); //returns a promise from the taskFunction
}

//TASK was to write this function
async function implementParallelTasks(tasks, maxParallelRequests, taskFn){
    workers = [];
	while(tasks.length > 0){
		for(i = 0; i < maxParallelRequests; i++){
			workers.push(exec(taskFn, tasks.pop()));
		}
		await Promise.all(workers);//Promise.all() can handle already resolved promises. It doesn't trigger them again but includes their resolved values in the final result.
		console.log(`DONE : Completed ${workers.length} tasks`);
	}
}

tasks = [1,2,3,4,5,6,7,8,9];
console.log(`There are ${tasks.length} tasks to finish`)
implementParallelTasks(tasks, 7, taskFunction)

/*
OUTPUT PRINTS : 
There are 9 tasks to finish
Finished task7
Finished task8
Finished task9
Completed 3 tasks
Finished task4
Finished task5
Finished task6
Completed 6 tasks
Finished task1
Finished task2
Finished task3
DONE : Completed 9 tasks

Even though 9 got popped first, 7 executes fastest compared to 7,8,9 as it only waits 7s so it gets printed first
*/
