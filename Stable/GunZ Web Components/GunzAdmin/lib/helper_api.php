<?PHP

# 2�����迭���� $dimension �׸����� ��Ʈ�Ѵ�.
function dArray_sort($arr, $dimension)
{
  if ($dimension !== 0)
  {
    for ($i = 0; $i < sizeof($arr); $i++)
    {
      array_unshift($arr[$i], $arr[$i][$dimension]);
    }
    sort($arr);
    for ($i=0; $i < sizeof($arr); $i++)
    {
      array_shift($arr[$i]);
    }
  } else {
    sort($arr);
  }
  
  return $arr;
}


## ���� üũ - �����������Ʈ������ ���
function check_session()
{
	session_start();
	$sess_login = $_SESSION["Login"];
	if (!$sess_login || $sess_login=="")
	{
		header("Location: /login.html");
	}
}

?>
