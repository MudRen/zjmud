// rank.c

#include <ansi.h>

inherit F_CLEAN_UP;

private int   do_normal(object me, string arg);
private int   do_rank(object me, object ob, string arg);
private mixed check_rank(string arg);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	string who;
	string rank;

	if (! arg)
	{
		rank = RANK_D->query_rank(me);
		write("�����ڵĽ���ͷ�Σ�" + rank + "\n");
		return 1;
	}

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return do_normal(me, arg);

	if (sscanf(arg, "%s %s", who, arg) != 2)
		return notify_fail("��μ� help rank ��ø������ʹ�÷�����\n");

	if (who == "me")
		ob = me;
	else
		ob = find_player(who);

	if (! objectp(ob))
		return notify_fail("û�������ҡ�\n");

	return do_rank(me, ob, arg);
}

// ��ͨ���ʹ�� rank ����
private int do_normal(object me, string arg)
{
	if (! wiz_level(me) &&
	    time() - me->query_temp("last/set_rank") > 3600)
	{
		if (! me->query_temp("pending/set_rank"))
		{
			write("����Ҫ����һ�����ƽ�������ѣ������ȷ������������һ��������\n");
			me->set_temp("pending/set_rank", 1);
			return 1;
		}

		if (me->query("balance") < 100000000)
			return notify_fail("��Ǯׯ�Ĵ�����\n");

		me->add("balance", -100000000);
		write("�����˳���Ϸ֮ǰ��������ʮ���ӵ�ʱ����������趨���ͷ�Ρ�\n");
		me->set_temp("last/set_rank", time());
	}

	return do_rank(me, me, arg);
}

int do_rank(object me, object ob, string arg)
{
	if (! stringp(arg = check_rank(arg)))
		return 0;

	ob->set("rank_info/rank", arg);
	write("���趨����" + (me == ob ? "�Լ�" : ob->name(1)) + "��ͷ�Ρ�\n");
	return 1;
}

private mixed check_rank(string arg)
{
	int len;
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	if ((len = strlen(filter_color(arg))) > 8)
		return notify_fail("���ͷ�β��ܳ����ĸ����֡�\n");

	while (len++ < 8)
	{
		arg += " ";
		if (len++ < 8)
			arg = " " + arg;
	}
	if (strlen(arg) > 100)
		return notify_fail("������̫���ˣ�Ϊ�˽�Լ��Դ�����������趨��\n");

	return arg + NOR + HIY;
}

int help(object me)
{
	write(@HELP
�������û�о�����Ȩ����ң�
ָ���ʽ : rank [<ͷ��>]

��������������趨�ƺţ��޸ĳƺ�����Ҫ��������һ��
���ƽ��Զ������Ǯׯ�˺��Ͽ۳�������δ�˳���Ϸ����
ʮ���������ٴ��޸Ĳ���Ҫ�����κ��������á�

��ע�⣺�趨�ĳƺŲ�ҪΥ����Ϸ���򣬷������������
�������Ĵ��������⽫ͷ������Ϊϵͳ��������ʦͷ�λ�
������۵�ͷ�ν�������ɢ������һ�������Ϣ����ȡ��
ͷ���⽫�ᰴ�չ��򴦷���

������Ǿ���ʹ�ø�����Ȩ�޵���һ���ʦ��
ָ���ʽ : rank <���> <ͷ��>
 
���ָ���������Ϊĳ��ȡһ��������ͷ�Σ�����ֻ����
ʦ�ſ���ʹ�ã������ϣ���������ʹ�� ANSI �Ŀ�����
Ԫ�ı���ɫ�����������µĿ����ִ���

$BLK$ - ��ɫ		$NOR$ - �ָ�������ɫ
$RED$ - ��ɫ		$HIR$ - ����ɫ
$GRN$ - ��ɫ		$HIG$ - ����ɫ
$YEL$ - ����ɫ		$HIY$ - ��ɫ
$BLU$ - ����ɫ		$HIB$ - ��ɫ
$MAG$ - ǳ��ɫ		$HIM$ - �ۺ�ɫ
$CYN$ - ����ɫ		$HIC$ - ����ɫ
$WHT$ - ǳ��ɫ		$HIW$ - ��ɫ
 
����ϵͳ�Զ������ִ�β�˼�һ�� $NOR$��
HELP );
	return 1;
}
