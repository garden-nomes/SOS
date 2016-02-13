/*
 * Midterm problem 3
 * Noah Weiner
 *
 * Assume that you have a queue implementation (with enqueue, dequeue, isEmpty). Add a "member" method
 * to the queue datstructure to combine two queues by merging every other element of the queue. Ie. if
 * Q1 = [a1, a2, a3] and Q2 = [b1, b2, b3] with a1 and b1 the fronts of their respective queues, the
 * result queue should be R = [a1, b1, a2, b2, a3, b3, ...]. Give the big-O of your function (assume
 * that enqueue is O(n) and dequeue is O(n)).
 *
 * Running time is O(n^2)
 */

class Queue {
	public:

		// ....

		Queue& combine(Queue q) {
			Queue result;

			while (!isEmpty() || !q.isEmpty()) {
				if (!isEmpty()) result.enqueue(dequeue());
				if (!q.isEmpty()) result.enqueue(q.dequeue());
			}

			*this = result;
			return result;
		}

		// ....
};
