// quester.c ������������

int is_quester() { return 1; }

// ����ѯ��
mixed accept_ask(object who, string topic)
{
	return QUEST_D->accept_ask(this_object(), who, topic);
}

// ��������
int ask_quest(object who)
{
	return QUEST_D->ask_quest(this_object(), who);
}

// ������Ʒ
int accept_object(object who, object ob)
{
	return QUEST_D->accept_object(this_object(), who, ob);
}

// ȡ������
int cancel_quest(object who)
{
	return QUEST_D->cancel_quest(this_object(), who);
}

