string ask_for_join()
{
	object me;

	me = this_player();
	if (me->query("family/family_name") != "������")
		return ("��Ͷ���û��ԨԴ��ƶ�᲻�Ҹ�����ȡ�");

	if ((string)me->query("class") == "bonze")
		return "�����ӷ𣡳����˲���ڿ����Ѿ������׼����ˡ�";

	if ((string)me->query("gender") != "Ů��")
		return "�����ӷ����գ����գ�ʩ������������ҷ𣬿�ȥ�������ܽ䡣";

	if (me->query("couple/id"))
		return me->name(1) + "�㳾Եδ�ˣ����ܳ��ң�";

	me->set_temp("pending/join_bonze", 1);
	command ("say �����ӷ����գ����գ�ʩ�������������"
		 "�������(kneel)�ܽ䡣");
	return "��ס����Ȼ���˼ң���һ����𣬲��ܻ��ס�";
}

int do_kneel()
{
	object me = this_player();
	string *prename = ({ "��", "��", "��", "��"});
	string name, new_name;

	if (! me->query_temp("pending/join_bonze"))
		return notify_fail("���ڵ��Ϲ���һ�����û�����㡣\n");

	message_vision(
		"$N��˫�ֺ�ʮ�����������ع���������\n\n"
		"$n����$N˵�����ðɣ�����ڱ������аɡ�\n\n"
		"$n������ƣ���$Nͷ�������Ħ���˼��£���$N��ͷ��������ȥ��\n\n",
		me, this_object());
	name = me->query("purename");
	if (! name) name = me->query("name");
	new_name = prename[random(sizeof(prename))] + name[0..1];
	command("say �ӽ��Ժ���ķ�������" + new_name + "��");
	command("chat " + name + "����Ϊ�ᣬ�ڶ���ɽ���У�ȡ����" + new_name + "��");
	command("smile");
	me->set("marks/old_name",name);
	me->delete_temp("pending/join_bonze");
	me->set("name", new_name);
	me->set("class", "bonze");
	me->set("K_record", me->query("PKS") + me->query("MKS"));
	me->set("shen_record", me->query("shen"));
	me->set("shen", 0);

	return 1;
}

void init()
{
	add_action("do_kneel", "kneel");
}
