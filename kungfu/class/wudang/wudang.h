// check recruit

int permit_recruit(object ob)
{
	if( ob->query("detach/�䵱��") || ob->query("betrayer/�䵱��") )
	{
		command("say �㵱���Ȼ�뿪�䵱�ɣ��α���Ҫ������");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say �����䵱�����������ɣ���������ʦ֮ͽ��");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "�䵱��" )
	{
		command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ���������䵱��������");
		return 0;
	}

	return 1;
}
