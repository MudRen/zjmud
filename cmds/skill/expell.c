// expell.c

#include <skill.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	string *skname;
	mapping skills;
	int i;

	if( !arg || !ob = present(arg, environment(me)) )
		return notify_fail("��Ҫ��˭���ʦ�ţ�\n");

	if( !ob->is_character() )
		return notify_fail("������ˣ��������ˣ����𲻶�����\n");

	if( !userp(ob) )
		return notify_fail("��ֻ�ܿ�����������ݵ����\n");

    if( !ob->is_apprentice_of(me) )
		return notify_fail("����˲�����ĵ��ӡ�\n");

    if( ob->query_temp("pending/detach"))
    {
	message_vision("\n$Nʹ�ĵĶ�$n˵�����������ܴ�����" +
		       ob->query("family/family_name") +
		       "���ε���ǰ;�����ˣ����ˣ�\n", me, ob);
    } else
    {
		message_vision("\n$N����$n˵�����ӽ���������Ҳ������"
			+ me->query("family/family_name") + "�ĵ����ˣ����߰ɣ�\n",
			me, ob);
	}

    tell_object(ob, "\n�㱻ʦ�������ʦ���ˣ�\n");

    ob->skill_expell_penalty();
    ob->add("detach/times", 1);
    ob->add("detach/" + ob->query("family/family_name"), 1);
	ob->delete("family");
	ob->set("title", "��ͨ����");
    ob->unconcious();

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : expell|kaichu <ĳ��>
 
���ָ��������㿪�����ɲŵĵ��ӣ����������뿪ʦ�ŵĵ��ӡ���������
�������б��ŵ���ѧ���ᱻ׷�أ�����������֪ʶ������⼼�ܶ����ܻ���
���������һ�����������һ�������������ء��Ĵ���������ڿ���һ����
��֮ǰ����������ǡ�
 
HELP
	);
	return 1;
}
