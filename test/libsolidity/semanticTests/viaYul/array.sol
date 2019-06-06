contract C {
	uint[] storageArray;
	function test_storage_array() public returns (uint256)
	{
		storageArray.length = 7;
		require(storageArray.length == 7);

		storageArray.length = 5;
		require(storageArray.length == 5);
		storageArray.length = 0;
		require(storageArray.length == 0);
		storageArray.length = 7;
		require(storageArray.length == 7);

		return storageArray.length;
	}
}
// ====
// compileViaYul: true
// ----
// test_storage_array() -> 7
