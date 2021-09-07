// snowman.
// yuj.

#include <ansi.h>
inherit F_CLEAN_UP;

void do_recover(object ob, int j)
{
	int i;
	mapping skills, learned;
	string *sk;

	if (j < 1 || j > 5) return;
	while(j--) {
		skills = ob->query_skills();
		if (mapp(skills)) {
			sk = keys(skills);
			ob->improve_skill(sk[0], 1, 1);
			learned = ob->query_learned();
			learned[sk[0]]--;
			foreach (string skill in sk) {
				if(SKILL_D(skill)->type()=="knowledge") continue;
				i = (skills[skill]+1)*(skills[skill]+1);
				if ((learned[skill]+=i/2) > i) {
					skills[skill]++;
					learned[skill] -= i;
				}
			}
		}
		ob->add("combat_exp", ob->query("combat_exp")*2/100);
		ob->add("shen", ob->query("shen")/10);
		ob->add("weiwang", ob->query("weiwang")/10);
		ob->add("score", ob->query("score")/10);
	}
	ob->reincarnate();
}

int main(object me, string arg)
{
	int i, j = 1;
	string obj, reason;
	object ob;
	mapping note;

	if( !arg )
		return notify_fail("recover <ĳ��> [����] because [ԭ��]��\n");

	if( sscanf(arg, "%s %d because %s", obj, i, reason)==3 ) j = i;
	else obj = arg;

	if( !reason )
		return notify_fail("recover <ĳ��> [����] because [ԭ��]��\n");

	ob = find_player(obj);
	if( !ob )  ob = find_living(obj);
	if( !ob )  ob = present(obj, environment(me));
	if( !ob ) return notify_fail("�Ҳ���������\n");

	if( !userp(ob) )
		return notify_fail("�Է�ֻ�Ǹ�NPC��������ôС������ɣ�\n");

	if( (wiz_level(me) < wiz_level("(wizard)")) && me!=ob )
		return notify_fail("��û�лָ�" + ob->name() + "������ʧ��Ȩ����\n");

	message_vision(HIR "\n$N����"+chinese_number(j)+"��"BLU"���"HIR"����$n���������У���$p�������ֻأ���\n"NOR"\n",me,ob);

	tell_object(ob, HIW"��е�����к��������ֱ�������֮�磬�ָ��˲�����ʧ��"NOR"\n");
	
	note = (["title":"�������ָ����ָ����"+ob->name(1) + "("+ capitalize(ob->query("id"))+")������ʧ�Ĺ���",
			"author":me->query("name") + "(" + getuid(me) + ")",
			"time":0,
			"msg":0,
			]);	
			
	if( ob!=me && !wizardp(ob) )
		log_file("static/DIECOVER",
			sprintf("%s(%s) recovered %s(%s) %d times because %s\n", me->name(1),
				me->query("id"), ob->name(1), ob->query("id"), j, reason
			), me, ({ ob->query("id") })
		);
	do_recover(ob, j);
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : recover <ĳ��> [����]

������ɻָ�������ʧ�����ã�

HELP
    );
    return 1;
}
