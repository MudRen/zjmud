// check recruit

int permit_recruit(object ob)
{
	if( ob->query("detach/��ң��") || ob->query("betrayer/��ң��") )
	{
		command("say �㵱�궼�Ѿ��뿪����ң�ɣ��α���Ҫ������");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say ������ң�����������ɣ���������ʦ֮ͽ��");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "��ң��" )
	{
		command("say ���Ȼ�Ѿ�������ʦָ�㣬���ú�ѧϰ����������ң��������");
		return 0;
	}

	return 1;
}
