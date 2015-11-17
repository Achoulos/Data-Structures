/* A fixed-sized hash map implemenation. *
 * Maps Strings to arbitrary Objects.    *
 * By Alex Choulos                       */

import java.lang.Math;

class Hashmap {

	// Context for each value for collision resolution.
	public enum Status {
		DELETED,
		EMPTY,
		FILLED
	}
	// Entry represents a single Hash Map value.
	class Entry {
		// Members of Entry.
		private Object object;
		private String key;
		private Status status;

		// Constructors.
		public Entry() {
			this.object = null;
			this.key = null;
			this.status = Status.EMPTY;
		}

		public Entry(Object object, Status status, String key) {
			this.key = key;
			this.object = object;
			this.status = status;
		}

		// Getters and Setters. 
		public void setKey(String string) {
			this.key = string;
		}
 		public void setObject(Object object) {
			this.object = object;
		}
		public void setStatus(Status status) {
			this.status = status;
		}
		public String getKey() {
			return this.key;
		}
		public Object getObject() {
			return this.object;
		}
		public Status getStatus() {
			return this.status;
		}
	}

	// Members of Hashmap.
	private Entry[] entries;
	private int filled;
	private int MAX_SIZE;

	public Hashmap (int size) {
		this.MAX_SIZE = size;
		this.filled = 0;
		this.entries = new Entry[size];
		for (int i = 0; i < size; i++) {
			this.entries[i] = new Entry();
		}
	}

	// Finds where a key belongs or where it should theoretically belong if it is not set.
	private int find(String key) {
		int position;
		int firstDeletedPosition = -1; 
		for (int i = 0; i < MAX_SIZE; i++) {
			position = Math.abs((key.hashCode() + i) % MAX_SIZE);

			if (this.entries[position].getStatus() == Status.EMPTY) {
				if (firstDeletedPosition == -1) {
					return position;
				} else {
					return firstDeletedPosition;
				}
			// Replace keys with new value. 
			} else if (this.entries[position].getStatus() == Status.FILLED) {
				if (this.entries[position].getKey().equals(key)) {
					return position;
				}
			} else if (this.entries[position].getStatus() == Status.DELETED) {
				if (firstDeletedPosition == -1) {
					firstDeletedPosition = position;
				}
			} 
		}
		return firstDeletedPosition;
	}

	public boolean set(String key, Object value) {
		int position = find(key);
		if (position == -1) {
			return false;
		}
		if (MAX_SIZE == filled && (!this.entries[position].getKey().equals(key))) {
			return false;
		} else {
			if (this.entries[position].getStatus() != Status.FILLED) {
				this.filled ++;
			}
			this.entries[position] = new Entry(value, Status.FILLED, key);
			return true;
		}
	}

	public Object get(String key) {
		if (this.filled == 0) {
			return null;
		} else {
			int position = find(key);
			if (position != -1) {
				return this.entries[position].getObject();
			} else {
				return null;
			}
		}
	}

	public Object delete(String key) {
		if (this.filled == 0) {
			return null;
		} else {
			int position = find(key);
			if (position != -1) {
				if(this.entries[position].getKey() == key) {
					Object o = this.entries[position].getObject();
					this.entries[position] = new Entry(null, Status.DELETED, null);
					this.filled --;
					return o;
				} else {
					return null;
				}
			} else {
				return null;
			}
		}
	}

	public float load() {
		return (float) filled / MAX_SIZE;
	}

	/*			   *
	 * Unit Tests. *
	 *  		   */

	public static void main(String[] args) {

		Hashmap map = new Hashmap(5);

		// Succcessfully store a variety of different object referencecs in a Hash Map.
		int integers[] = {1, 2, 3, 4, 5};
		boolean m = true;
		int one = 1;

		assert(map.set("ONE", one)) : "Key-value pair failed to set.";
		assert(map.set("Greeting", "Hello")) : "Key-value pair failed to set.";
		assert(map.set("INTEGERS", integers)) : "Key-value pair failed to set.";
		assert(map.set("Map", m)) : "Key-value pair failed to set.";
		assert(map.set("dokie", "heart")) : "Key-value pair failed to set.";

		assert((int) map.get("ONE") == one) : "Failed to get previously 'set' value.";
		assert(map.get("Greeting").equals("Hello")) : "Failed to get previously 'set' value.";
		assert(map.get("INTEGERS") == integers) : "Failed to get previously 'set' value.";
		assert((boolean) map.get("Map") == m) : "Failed to get previously 'set' value.";
		assert(map.get("dokie").equals("heart")) : "Failed to get previously 'set' value.";
		assert(map.load() == 1) : "Map load factor is not '1' in a full hash map.";

		// Fails to add another entry to a full Hash Map.

		assert(map.set("fail", false) == false) : "Set method returned a 'true' value in a full hashmap.";
		assert(map.get("fail") == null) : "Get method retrieved a set value that should not exist.";

		// Overrides an already existent key.

		assert(map.set("Greeting", "dokie"));
		assert(map.get("Greeting").equals("dokie")) : "Map key failed to overwrite same existing key.";

		// Sucessfully delete

		assert(map.delete("Greeting").equals("dokie")) : "Deleted key did not match set value.";
		assert(map.get("Greeting") == null) : "Deleted value was not removed from hashmap.";

		// Unable to delete a non-existent key.

		assert(map.delete("non-existent") == null) : "Deleted non-existent value in Map.";

		// Successfully add after deleting.

		assert(map.set("Greeting", 45)) : "Failed to set a new value after Hashmap deletion.";

		// Delete everything, check correct objects are returned.

		assert((int) map.delete("ONE") == one) : "Deleted object did not match set object.";
		assert((int) map.delete("Greeting") == 45) : "Deleted object did not match set object.";
		assert(map.delete("INTEGERS") == integers) : "Deleted object did not match set object.";
		assert((boolean) map.delete("Map") == m) : "Deleted object did not match set object.";
		assert(map.delete("dokie").equals("heart")) : "Deleted object did not match set object.";
		assert(map.load() == 0) : "Supposedly empty hashmap did not have load factor of 0";

		// Delete from an empty Map.

		assert(map.delete("empty") == null) : "Delete operation in an empty hashmap returned non-null value.";
		assert(map.load() == 0) : "Deleted value from empty hashmap caused load factor to not be equal to 0.";

		// Re-add everything.

		String[] s = {"Hello", "How", "Are", "You"};
		assert(map.set("50s", 50)) : "Failed to set values in previously filled, but now empty hashmap.";
		assert(map.set("Strings", s)) : "Failed to set values in previously filled, but now empty hashmap.";
		assert(map.set("Haha", "")) : "Failed to set values in previously filled, but now empty hashmap.";
		assert(map.set("True", true)) : "Failed to set values in previously filled, but now empty hashmap.";
		assert(map.set("False", false)) : "Failed to set values in previously filled, but now empty hashmap.";

		assert((int) map.get("50s") == 50) : "Failed to get values from previously filled, but now empty hashmap.";
		assert(map.get("Strings") == s) : "Failed to get values from previously filled, but now empty hashmap.";
		assert(map.get("Haha").equals("")) : "Failed to get values from previously filled, but now empty hashmap.";
		assert((boolean) map.get("True") == true) : "Failed to get values from previously filled, but now empty hashmap.";
		assert((boolean) map.get("False") == false) : "Failed to get values from previously filled, but now empty hashmap.";
		assert(map.load() == 1) : "Load factor is not equal to 1 despite full hashmap.";
	}
}