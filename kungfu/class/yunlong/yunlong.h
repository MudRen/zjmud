// check recruit

int permit_recruit(object ob)
{
	if (ob->query("detach/������") || ob->query("betrayer/������"))
	{
		command("say �㵱���Ȼ�뿪�������ǣ��Ͳ��ػ����ˣ�");
		return 0;
	}

	if (ob->query("betrayer/times"))
	{
		command("say ���������ŷ��帴��������壬���߰ɣ�");
		return 0;
	}

	if (ob->query("family/family_name") &&
	    ob->query("family/family_name") != "������")
	{
		command("sigh");
		command("shake");
		return 0;
	}

	return 1;
}
