// lingjiu.h

int permit_recruit(object ob)
{
	if( ob->query("detach/���չ�") ||
	    ob->query("betrayer/���չ�") )
	{
		command("say �뿪����翷�Ͳ�Ҫ�ٻ�����");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say ���²��Ҳ��ţ��������չ���޵ľ����������ˡ�");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "���չ�" )
	{
		command("say ������ʦ�����Ͳ�Ҫ���������չ��ˣ�");
		return 0;
	}

	return 1;
}
