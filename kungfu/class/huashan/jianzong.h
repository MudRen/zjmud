// qizong.h

int permit_recruit(object ob)
{
	if( ob->query("family/family_name") == "��ɽ��1" )
	{
		command("say �ߣ��㻹�Ǹ���α��������ѧϰʲô���ڵ��书�ɡ�");
		return 0;
	}

	if( ob->query("detach/��ɽ����") ||
	    ob->query("betrayer/��ɽ����") )
	{
		command("say ��ɽ���Խ�δ���չ����ŵ��ӣ�");
		return 0;
	}

	if( ob->query("betrayer/times") )
	{
		command("say ��ɽ�ɽ����ľ������壬������ʦ֮��������⣿");
		return 0;
	}

	if( ob->query("family/family_name") && ob->query("family/family_name") != "��ɽ��" &&
	    ob->query("family/family_name") != "��ɽ����" )
	{
		command("say ���������ʦָ�㣬���α������ǻ�ɽ�ɣ�");
		return 0;
	}

	return 1;
}
