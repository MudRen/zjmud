// ouyang.h

int permit_recruit(object ob)
{
	object me;

	me = this_object();
	if (ob->query("name") == "ŷ����" ||
	    ob->query("name") == "ŷ����")
	{
		message_vision("$N��ŭ���Ҳ٣��������������ʲô��˼����\n",
			       this_object());
		return 0;
	}

	if (ob->query("born_family") != "ŷ������"&&ob->query("haha1"))
	{
		message_vision("$N��$n�����㲻������ŷ���ҵ��ˣ�����������Ϊͽ��\n",
			       me, ob);
		return 0;
	}

	if (ob->query("detach/ŷ������") ||
	    ob->query("betrayer/times"))
	{
		message_vision("$Nҡҡͷ��$n˵���㷴���޳����Ҳ�������Ϊͽ��\n",
			       me, ob);
		return 0;
	}

	if (ob->query("family/family_name") &&
	    ob->query("family/family_name") != me->query("family/family_name"))
	{
		message_vision("$N��$n��������Ȼ��ŷ���ҵ��ˣ����������������ɣ��Ҳ�������Ϊͽ��\n",
			       me, ob);
		return 0;
	}

	return 1;
}
