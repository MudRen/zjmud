// ultra.h ��ʦ������ҵĹ�������

int calc_level(object me, string skill);
void check_ultra(object me);

// check level
// level is calculate as:
// level = (skill effect level) + (action["force"] - 200) / 5
mapping opinions_rank = ([
	415 : "��ʦ",
	390 : "�Ƿ��켫",
	385 : "��������",
	340 : "��������",
	315 : "¯����",
	290 : "���д��",
	265 : "��ͬ����",
	240 : "�������",
	215 : "���ֲ���",
	190 : "����С��",
]);

// generate opinion
void check_opinion(object me)
{
	string msg;
	string rank;
	int *ks;
	int lvl;
	int next_lvl;
	int opinion;
	int i;

	delete_temp("opinion");
	if (! me || environment(me) != environment())
	{
		command("sigh");
		return;
	}

	// rank: ԭ�е����۳ƺ�
	// ks:   ��ͬ������Ҫ�ĵȼ�������������
	// lvl:  ԭ���������ڵĵȼ�
	// next_lvl: ��ԭ�е���������һ�ȼ���Ҫ��lvl
	// opinion : �˴ε����۵ȼ������Ϊ-1��û�б仯
	rank = me->query("opinion/" MY_OPINION);
	ks  = sort_array(keys(opinions_rank), 1);
	if (! stringp(rank))
	{
		// ��ǰû�����ۣ�������С������Ҫ�ĵȼ�
		next_lvl = ks[0];
	} else
	{
		// ��ǰ�����ۣ�����һ����������Ļ���Ҫ
		// �����ټ�
		for (i = 0; i < sizeof(ks) - 1; i++)
			if (opinions_rank[ks[i]] == rank)
			{
				next_lvl = ks[i + 1];
				break;
			}
		if (i >= sizeof(ks))
		{
			// �޷��ҵ�ԭ�ȵĵȼ���������С����
			next_lvl = ks[0];
		}
	}
	opinion = -1;
	for (i = 0; i < sizeof(my_opinions); i++)
	{
		lvl = calc_level(me, my_opinions[i]);
		if (lvl >= next_lvl && lvl > opinion)
			// ��¼����i����ѧ�и��õ�����
			opinion = lvl;
	}

	if (opinion == -1)
	{
		if (next_lvl == ks[0])
		{
			message_vision("\n$N����һЦ����$n����"
				       "�����" OPINION_TYPE "���а����ú�"
				       "Ŭ���ɣ���\n", this_object(), me);
			return;
		}
		message_vision("\n$N��$nҡҡͷ����������ô������"
			       "�������" OPINION_TYPE
			       "���ϴ�ûʲô̫��Ľ�������\n",
			       this_object(), me);
		return;
	}

	for (i = sizeof(ks) - 1; i > 0; i--)
		if (opinion >= ks[i]) break;

	me->set("opinion/" MY_OPINION, opinions_rank[ks[i]]);
	if (i == sizeof(ks) -1)
	{
		// �����ռ�
		message_vision("\n$N��$nЦ��������ϲ��" +
			       RANK_D->query_respect(me) +
			       "��" OPINION_TYPE "��Ȼ������ʦ���磡"
			       "�������������أ���\n",
			       this_object(), me);
		me->set("opinions/master", 1);
		check_ultra(me);
		return;
	}

	message_vision("\n$N��˼Ƭ�̣���$n��������Ŀǰ���������"
		       OPINION_TYPE "�Ѿ������������" +
		       opinions_rank[ks[i]] + "�ˡ���\n",
		       this_object(), me);
}

void check_ultra(object me)
{
	object *ultra;

	if (me->query("opinion/unarmed") != "��ʦ" ||
	    me->query("opinion/weapon") != "��ʦ"  ||
	    me->query("opinion/force") != "��ʦ"  ||
	    me->query("opinion/dodge") != "��ʦ" )
		return;

	me->set("opinion/ultra", 1);
	ultra = NPC_D->query_ultra_master();
	ultra -= ({ this_object() });
	command("chat ���ǳ���������ǰ�ˣ��벻����������" + me->query("name") +
		"�������ִ���ʦ�����У�");
	ultra->do_congration(me);
	CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
			      "��˵" + me->query("name") + "��Ϊ��ѧ����ʦ��");
}
