// xingxiu.h

int welcome(object ob)
{
	if( ob->query("detach/������") || ob->query("betrayer/������") )
	{
		command("say ������������ȥ�������������ɺðɣ�");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say û��ϵ������Ȼ�й�����ʦ�����������������Ͷ������ϲ�ɺأ�");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "������" )
	{
		command("say �Ǻǣ��ð���" + ob->query("family/family_name") +
			"��ʲô��");
		return 0;
	}

	return 1;
}
