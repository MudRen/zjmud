// check recruit

int permit_recruit(object ob)
{
	if (ob->query("detach/ѩɽ��") || ob->query("betrayer/ѩɽ��"))
	{
		command("say ���뿪��ѩɽ���ǣ�ѩɽ���Ѿ��������ˣ�");
		return 0;
	}

	if (ob->query("betrayer/times"))
	{
		command("say ����ѩɽ�������ʦ֮ͽ���㻹�������");
		return 0;
	}

	if (ob->query("family/family_name") &&
	    ob->query("family/family_name") != "ѩɽ��")
	{
		command("say ����ʦ��ָ�㣬��ѭ�򽥽�������óȻ��ʦ��");
		return 0;
	}

	return 1;
}
