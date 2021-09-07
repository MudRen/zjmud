// call.c
// updated by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string objname, func, param, euid;
	object obj;
	object arg_ob;
	mixed *args, result;
	mapping info, linfo;
	int e;
	int i;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (arg)
	{
		if (sscanf(arg, "-%s %s", euid, arg) == 2)
		{
			if ((string)SECURITY_D->get_status(me) != "(admin)")
				return notify_fail("�㲻���趨�Լ��� euid��\n");
			seteuid(euid);
		}
		else
			seteuid(geteuid(this_player()));

		if (sscanf(arg, "%s->%s(%s", objname, func, param) != 3)
			return notify_fail("ָ���ʽ��call <���>-><����>( <����>, ... )\n");
	} else
		return notify_fail("ָ���ʽ��call <���>-><����>( <����>, ... )\n");

	if (strlen(param) >= 1 && param[strlen(param) - 1] == ')')
		param = param[0..<2];

	obj = present(objname, environment(me));
	if (! obj) obj = present(objname, me);
	if (! obj) obj = find_player(objname);
	if (! obj || ! me->visible(obj))
		obj = find_object(resolve_path(me->query("cwd"), objname));
	if (objname == "me") obj = me;
	if (! obj) return notify_fail("�Ҳ���ָ���������\n");

	if (playerp(obj) && wiz_level(me) >= wiz_level(obj) ||
	    obj->item_owner() == me->query("id"))
	{
		log_file("static/call_player",
			sprintf("%s %-9s call %s(%s)->%s(%s)\n",
				log_time(),
				geteuid(me),
				obj->name(1), geteuid(obj), func, param));
	} else
	if (! master()->valid_write(base_name(obj), me, "set"))
		return notify_fail("��û��ֱ�Ӻ����������ĺ�����Ȩ����\n");

	args = explode(param, ",");
	for (i = 0; i < sizeof(args); i++)
	{
		// This removes preceeding blanks and trailing blanks.
		parse_command(args[i], environment(me), "%s", args[i]);
		if (sscanf(args[i], "%d", args[i])) continue;
		if (sscanf(args[i], "\"%s\"", args[i]))
		{
			args[i] = replace_string(args[i], "\\n", "\n");
			args[i] = color_filter(args[i]);
			continue;
		}
		if (arg_ob = find_object(args[i]))
			args[i] = arg_ob;
	}

	if (func == "set" && playerp(obj) &&
	    sizeof(args) && args[0] == "name")
	{
		write(HIY "���鲻Ҫ�� call �����޸���ҵ���"
		      "�֣���μ� changename ���"NOR"\n");
	}

	args = ({ func }) + args;

	info = rusage();
	e = eval_cost();
	if (catch(result = call_other(obj, args)))
	{
		write(HIR "�����з����˴���"NOR"\n");
		return 1;
	}

	e -= eval_cost();
	linfo = rusage();

	for (i = 1; i < sizeof(args); i++)
		args[i] = sprintf("%O", args[i]);

	me->start_more(sprintf("%O->%s(%s) = %O\n"
			       WHT "Total eval cost:%d  CPU time: %d+%d ����"NOR"\n",
			       obj, func, 
			       implode(args[1..sizeof(args)-1], ", "), result, e,
			       linfo["utime"] - info["utime"],
			       linfo["stime"] - info["stime"]));
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : call <���>-><����>(<����>, ...... )
 
����<���>���<����>���������<����>.

�������ڿ��Ա���Ȩʹ�õ���Ϣ������
self��npc��user��nonechar��wizard��all��

������findusr
HELP );
	return 1;
}

