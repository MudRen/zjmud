// taohua.h

int permit_recruit(object ob)
{
	if( ob->query("detach/�һ���") ||
	    ob->query("betrayer/�һ���") )
	{
		command("say ���㻹�������һ���������");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say ���²��Ҳ��ţ�����ʹ�����������ˡ�");
		return 0;
	}

	if( ob->query("family/family_name") &&
	    ob->query("family/family_name") != "�һ���" )
	{
		command("say ���������ʦָ�㣬���������һ�����ʲô��");
		return 0;
	}

	return 1;
}
