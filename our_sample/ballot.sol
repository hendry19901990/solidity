pragma solidity >=0.7.0 <0.9.0;

contract Ballot {
   function use_our_code(bytes32 _content) public view returns (bytes32){
      bytes32 r = upper(_content);
      return r;
   }
}
