// ben.h for fight

int accept_touxi(object ob)
{
	object kr;

	if (is_killing(ob->query("id")))
		return 1;

	if (! objectp(kr = present("ku rong")))
		return 1;

	command("say ���ٴ�ʦ����" + RANK_D->query_rude(ob) +
		"�����񣬾�Ȼ���ְ��㣡");
	kr->start_fight(ob);
    	return 1;
}

int accept_hit(object ob)
{
	object kr;

	if (is_killing(ob->query("id")))
		return 1;

	if (! objectp(kr = present("ku rong")))
		return 1;

	command("say ���ٴ�ʦ����" + RANK_D->query_rude(ob) +
		"���������ˣ�");
	kr->start_fight(ob);
    	return 1;
}

int accept_kill(object ob)
{
	object kr;

	if (is_killing(ob->query("id")))
		return 1;

	if (! objectp(kr = present("ku rong")))
		return 1;

	command("say ���ٴ�ʦ����" + RANK_D->query_rude(ob) +
		"��ͼ���ף�ǿ�����ף�");
	kr->start_fight(ob);
	return 1;
}

int accept_fight(object ob)
{
	command("say ���գ����գ�ʩ���γ����ԣ�");
    	return 0;
}

int accept_ansuan(object ob)
{
	return notify_fail("��������ׯ�ϣ��㲻��óȻ���֡�\n");
}
